// Copyright 2022 Hansem Ro <hansemro@outlook.com>
// Copyright 2026 Jared Sutton (@jpsutton)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdint.h>

// Bit-banged serial interface of a single Macroblock MBI5042 (16-channel
// constant-current sink with 16-bit PWM). Based on hansemro's MasterKeys driver.

#define MBI5042_CHANNELS 16

// Instructions are the number of DCLK pulses while LE is high.
#define MBI5042_DATA_LATCH 1
#define MBI5042_GLOBAL_LATCH 3
#define MBI5042_READ_CONFIGURATION 5
#define MBI5042_WRITE_CONFIGURATION 11
#define MBI5042_ENABLE_WRITE_CONFIGURATION 15

void mbi5042_init_pins(void);
void mbi5042_send_instruction(uint8_t instr);
void mbi5042_write_configuration(uint16_t config);
// Loads one 16-bit grayscale value per channel and makes them active.
void mbi5042_write_grayscale(const uint16_t gray[MBI5042_CHANNELS]);
// Number of DCLK pulses before a 1 reaches SDO (16 for one chip), or 0 if it
// never does.
uint8_t mbi5042_shift_register_length(void);
