// Copyright 2022 Hansem Ro <hansemro@outlook.com>
// Copyright 2026 Jared Sutton (@jpsutton)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "mbi5042.h"

static inline void dclk_pulse(void) {
    __NOP();
    __NOP();
    gpio_write_pin_low(MBI5042_DCLK_PIN);
    __NOP();
    __NOP();
    gpio_write_pin_high(MBI5042_DCLK_PIN);
}

// Shifts the top `bits` bits of `data` out MSB first, holding LE high for the
// last `le_bits` clocks.
static void shift_out(uint16_t data, uint8_t bits, uint8_t le_bits) {
    gpio_write_pin_low(MBI5042_LE_PIN);
    while (bits > 0) {
        if (bits == le_bits) {
            gpio_write_pin_high(MBI5042_LE_PIN);
        }
        __NOP();
        __NOP();
        gpio_write_pin_low(MBI5042_DCLK_PIN);
        gpio_write_pin(MBI5042_SDI_PIN, data & 0x8000);
        __NOP();
        __NOP();
        gpio_write_pin_high(MBI5042_DCLK_PIN);
        data <<= 1;
        bits--;
    }
    gpio_write_pin_low(MBI5042_LE_PIN);
}

void mbi5042_init_pins(void) {
    gpio_set_pin_output(MBI5042_DCLK_PIN);
    gpio_set_pin_output(MBI5042_LE_PIN);
    gpio_set_pin_output(MBI5042_SDI_PIN);
    gpio_write_pin_high(MBI5042_DCLK_PIN);
    gpio_write_pin_low(MBI5042_LE_PIN);
    gpio_write_pin_low(MBI5042_SDI_PIN);
    gpio_set_pin_input(MBI5042_SDO_PIN);
}

void mbi5042_send_instruction(uint8_t instr) {
    gpio_write_pin_high(MBI5042_LE_PIN);
    while (instr-- > 0) {
        dclk_pulse();
    }
    gpio_write_pin_low(MBI5042_LE_PIN);
}

void mbi5042_write_configuration(uint16_t config) {
    mbi5042_send_instruction(MBI5042_ENABLE_WRITE_CONFIGURATION);
    shift_out(config << 6, 16, MBI5042_WRITE_CONFIGURATION);
}

void mbi5042_write_grayscale(const uint16_t gray[MBI5042_CHANNELS]) {
    // The first data latch fills output channel 15.
    for (int8_t ch = MBI5042_CHANNELS - 1; ch >= 0; ch--) {
        shift_out(gray[ch], 16, MBI5042_DATA_LATCH);
    }
    gpio_write_pin_low(MBI5042_SDI_PIN);
    mbi5042_send_instruction(MBI5042_GLOBAL_LATCH);
}

uint8_t mbi5042_shift_register_length(void) {
    shift_out(0, 16, 0);
    for (uint8_t len = 1; len <= 32; len++) {
        shift_out(0x8000, 1, 0);
        if (gpio_read_pin(MBI5042_SDO_PIN)) {
            return len;
        }
    }
    return 0;
}
