// Copyright 2026 Jared Sutton (@jpsutton)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// The stock IAP checks this RAM word after reset. 0x55AAFAF5 keeps it in the
// bootloader; the stock firmware writes it in its reset-to-IAP handler.
// The linker script keeps the last word of SRAM out of the image.
#define IAP_MAGIC_LOCATION 0x20003FFC
#define IAP_MAGIC_VALUE 0x55AAFAF5

// MBI5042 LED driver (U7) and LED row switches, from the stock firmware
// (notes/pinmap.md). The driver's supply is switched on by pulling PC11 low.
#define MBI5042_SDI_PIN C12
#define MBI5042_DCLK_PIN A14
#define MBI5042_LE_PIN A15
#define MBI5042_SDO_PIN B0
#define MBI5042_GCLK_PIN C10
#define LED_DRIVER_POWER_PIN C11
#define LED_ROW_PINS {C15, C14, B5, B4, B3, B2, D3, D2}
// Configuration word from hansemro's MasterKeys Pro L White port (same driver,
// same Cheng Yong platform).
#define MBI5042_CONFIG 0x12C
