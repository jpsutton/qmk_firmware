// Copyright 2026 Jared Sutton (@jpsutton)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "mbi5042.h"

// The stock IAP leaves the watchdog running; the stock app and hansemro's
// MasterKeys port both reload it from the scan loop.
#define WDT_CR 0x40068000
#define WDT_RELOAD 0x5FA00001

// Application header the stock IAP reads at 0x3BF8 (placed by
// ld/HT32F52352_MK_TYPIST.ld), copied from the stock app. The IAP only starts
// the application if the first word matches; its checksum command needs the
// second (0x01 = enabled, 0x34 = 52-byte re-key interval). The third is what
// the IAP returns for info read 0x12/0x01.
__attribute__((section(".iap_header"), used)) static const uint32_t iap_header[3] = {0x04040000, 0x34000001, 0x00020004};

// Indicator LEDs. All four sit on MBI5042 output 15, one per LED row: the stock
// firmware (FUN_00005a28) sets its LED plane slots 0x7C-0x7F, which are output
// 15 on rows 4-7. The rows are high-side switches that the stock firmware
// multiplexes over all 8 rows, so each indicator is lit 1/8 of the time. With
// only output 15 in use, the grayscale data is loaded once and the timer just
// steps through the rows.
static const pin_t led_rows[8] = LED_ROW_PINS;
enum { LED_ROW_LED4 = 4, LED_ROW_SCROLL = 5, LED_ROW_CAPS = 6, LED_ROW_NUM = 7 };
static volatile uint8_t led_lit; // bit n: LED on row n is on
static uint8_t          led_row;

static void led_refresh(GPTDriver *gptp) {
    gpio_write_pin_low(led_rows[led_row]);
    led_row = (led_row + 1) & 7;
    if (led_lit & (1 << led_row)) {
        gpio_write_pin_high(led_rows[led_row]);
    }
}

// 4 kHz per row, 500 Hz per LED
static const GPTConfig led_timer_config = {
    .frequency = 1000000,
    .callback  = led_refresh,
};

// MBI5042 grayscale clock, about 4 MHz on GPTM1 CH0
static const PWMConfig led_gclk_config = {
    .frequency = HT32_CK_AHB_FREQUENCY,
    .period    = HT32_CK_AHB_FREQUENCY / 4000000 - 1,
    .channels  = {[0] = {.mode = PWM_OUTPUT_ACTIVE_LOW}},
};

static void indicators_init(void) {
    for (uint8_t i = 0; i < 8; i++) {
        gpio_set_pin_output(led_rows[i]);
        gpio_write_pin_low(led_rows[i]);
    }
    mbi5042_init_pins();
    gpio_set_pin_output(LED_DRIVER_POWER_PIN);
    gpio_write_pin_low(LED_DRIVER_POWER_PIN);

    pwmStart(&PWMD_GPTM1, &led_gclk_config);
    palSetLineMode(MBI5042_GCLK_PIN, PAL_MODE_OUTPUT_PUSHPULL | PAL_HT32_MODE_AF(AFIO_TM));
    pwmEnableChannel(&PWMD_GPTM1, 0, PWM_FRACTION_TO_WIDTH(&PWMD_GPTM1, 2, 1));

    // Give the driver up to 100 ms after power-on to answer on SDO.
    for (uint8_t i = 0; i < 100 && mbi5042_shift_register_length() != MBI5042_CHANNELS; i++) {
        *((volatile uint32_t *)WDT_CR) = WDT_RELOAD;
        wait_ms(1);
    }
    mbi5042_write_configuration(MBI5042_CONFIG);
    uint16_t gray[MBI5042_CHANNELS] = {[15] = 0xFFFF};
    mbi5042_write_grayscale(gray);

    gptStart(&GPTD_BFTM1, &led_timer_config);
    gptStartContinuous(&GPTD_BFTM1, 250);
}

void keyboard_post_init_kb(void) {
    indicators_init();
    keyboard_post_init_user();
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
        led_lit = (led_state.num_lock << LED_ROW_NUM) | (led_state.caps_lock << LED_ROW_CAPS) | (led_state.scroll_lock << LED_ROW_SCROLL);
    }
    return res;
}

void matrix_scan_kb(void) {
    *((volatile uint32_t *)WDT_CR) = WDT_RELOAD;
    matrix_scan_user();
}

void mcu_reset(void) {
    __disable_irq();
    NVIC_SystemReset();
}

// Reboot into the stock Cheng Yong IAP (04D9:1301), as the stock firmware does.
void bootloader_jump(void) {
    *((volatile uint32_t *)IAP_MAGIC_LOCATION) = IAP_MAGIC_VALUE;
    __disable_irq();
    NVIC_SystemReset();
}
