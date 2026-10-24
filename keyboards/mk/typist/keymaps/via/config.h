// Copyright 2026 Jared Sutton (@jpsutton)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Placeholder until EEPROM moves to the SPI flash (wear_leveling + spi_flash).
// Transient EEPROM loses VIA changes on power-off.
#define TRANSIENT_EEPROM_SIZE 2048
