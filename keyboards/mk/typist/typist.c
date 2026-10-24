// Copyright 2026 Jared Sutton (@jpsutton)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

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
