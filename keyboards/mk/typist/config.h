// Copyright 2026 Jared Sutton (@jpsutton)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// The stock IAP checks this RAM word after reset. 0x55AAFAF5 keeps it in the
// bootloader; the stock firmware writes it in its reset-to-IAP handler.
// The linker script keeps the last word of SRAM out of the image.
#define IAP_MAGIC_LOCATION 0x20003FFC
#define IAP_MAGIC_VALUE 0x55AAFAF5
