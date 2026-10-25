// Copyright 2026 Jared Sutton (@jpsutton)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Indicator LEDs: MBI5042 grayscale clock and row refresh timer
#define HAL_USE_PWM TRUE
#define HAL_USE_GPT TRUE

#include_next <halconf.h>
