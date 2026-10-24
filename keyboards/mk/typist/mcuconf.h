// Copyright 2026 Jared Sutton (@jpsutton)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "nvic.h"

#define HT32F52352_MCUCONF

// 8 MHz HSE, PLL to 48 MHz for core and USB
#define HT32_CK_HSE_FREQUENCY 8000000UL
#define HT32_CKCU_SW CKCU_GCCR_SW_PLL
#define HT32_PLL_USE_HSE TRUE
#define HT32_PLL_FBDIV 6       // 8 MHz -> 48 MHz
#define HT32_PLL_OTDIV 0
#define HT32_AHB_PRESCALER 1   // 48 MHz
#define HT32_USART_PRESCALER 1 // 48 MHz
#define HT32_USB_PRESCALER 1   // 48 MHz

// SysTick uses processor clock at 48 MHz
#define HT32_ST_USE_HCLK TRUE

#define HT32_USB_USE_USB0 TRUE
#define HT32_USB_USB0_IRQ_PRIORITY 2
