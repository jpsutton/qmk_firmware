// Copyright 2026 Jared Sutton (@jpsutton)
// SPDX-License-Identifier: Apache-2.0

#include "hal.h"

// Pin map from the stock firmware (notes/pinmap.md). Every matrix pin is put on
// AF1 (GPIO); PB10/PB11/PB12 default to X32KIN/X32KOUT/RTCOUT, not GPIO.
#define PBIT(PORT, LINE) ((PAL_PORT(LINE) == PORT) ? (1 << PAL_PAD(LINE)) : 0)
#define PAFIO_L(PORT, LINE, AF) (((PAL_PORT(LINE) == PORT) && (PAL_PAD(LINE) < 8)) ? (AF << (PAL_PAD(LINE) << 2)) : 0)
#define PAFIO_H(PORT, LINE, AF) (((PAL_PORT(LINE) == PORT) && (PAL_PAD(LINE) >= 8)) ? (AF << ((PAL_PAD(LINE) - 8) << 2)) : 0)
#define PAFIO(PORT, N, LINE, AF) ((N) ? PAFIO_H(PORT, LINE, AF) : PAFIO_L(PORT, LINE, AF))

// Matrix strobes (QMK rows), driven low one at a time.
#define OUT_BITS(PORT) (PBIT(PORT, PAL_LINE(IOPORTD, 1)) | PBIT(PORT, PAL_LINE(IOPORTC, 1)) | PBIT(PORT, PAL_LINE(IOPORTD, 0)) | PBIT(PORT, PAL_LINE(IOPORTB, 8)) | PBIT(PORT, PAL_LINE(IOPORTA, 11)) | PBIT(PORT, PAL_LINE(IOPORTA, 0)) | PBIT(PORT, PAL_LINE(IOPORTA, 1)) | PBIT(PORT, PAL_LINE(IOPORTA, 2)) | PBIT(PORT, PAL_LINE(IOPORTA, 3)) | PBIT(PORT, PAL_LINE(IOPORTA, 4)) | PBIT(PORT, PAL_LINE(IOPORTC, 5)) | PBIT(PORT, PAL_LINE(IOPORTC, 9)) | PBIT(PORT, PAL_LINE(IOPORTC, 13)) | PBIT(PORT, PAL_LINE(IOPORTA, 10)) | PBIT(PORT, PAL_LINE(IOPORTB, 1)) | PBIT(PORT, PAL_LINE(IOPORTA, 8)) | 0)

// Matrix inputs (QMK cols), pulled up, active low.
#define IN_BITS(PORT) (PBIT(PORT, PAL_LINE(IOPORTC, 4)) | PBIT(PORT, PAL_LINE(IOPORTA, 5)) | PBIT(PORT, PAL_LINE(IOPORTA, 6)) | PBIT(PORT, PAL_LINE(IOPORTA, 7)) | PBIT(PORT, PAL_LINE(IOPORTC, 8)) | PBIT(PORT, PAL_LINE(IOPORTB, 10)) | PBIT(PORT, PAL_LINE(IOPORTB, 11)) | PBIT(PORT, PAL_LINE(IOPORTB, 12)) | 0)

#define AF_BITS(PORT, N) (PAFIO(PORT, N, PAL_LINE(IOPORTD, 1), AFIO_GPIO) | PAFIO(PORT, N, PAL_LINE(IOPORTC, 1), AFIO_GPIO) | PAFIO(PORT, N, PAL_LINE(IOPORTD, 0), AFIO_GPIO) | PAFIO(PORT, N, PAL_LINE(IOPORTB, 8), AFIO_GPIO) | PAFIO(PORT, N, PAL_LINE(IOPORTA, 11), AFIO_GPIO) | PAFIO(PORT, N, PAL_LINE(IOPORTA, 0), AFIO_GPIO) | PAFIO(PORT, N, PAL_LINE(IOPORTA, 1), AFIO_GPIO) | PAFIO(PORT, N, PAL_LINE(IOPORTA, 2), AFIO_GPIO) | PAFIO(PORT, N, PAL_LINE(IOPORTA, 3), AFIO_GPIO) | PAFIO(PORT, N, PAL_LINE(IOPORTA, 4), AFIO_GPIO) | PAFIO(PORT, N, PAL_LINE(IOPORTC, 5), AFIO_GPIO) | PAFIO(PORT, N, PAL_LINE(IOPORTC, 9), AFIO_GPIO) | PAFIO(PORT, N, PAL_LINE(IOPORTC, 13), AFIO_GPIO) | PAFIO(PORT, N, PAL_LINE(IOPORTA, 10), AFIO_GPIO) | PAFIO(PORT, N, PAL_LINE(IOPORTB, 1), AFIO_GPIO) | PAFIO(PORT, N, PAL_LINE(IOPORTA, 8), AFIO_GPIO) | PAFIO(PORT, N, PAL_LINE(IOPORTC, 4), AFIO_GPIO) | PAFIO(PORT, N, PAL_LINE(IOPORTA, 5), AFIO_GPIO) | PAFIO(PORT, N, PAL_LINE(IOPORTA, 6), AFIO_GPIO) | PAFIO(PORT, N, PAL_LINE(IOPORTA, 7), AFIO_GPIO) | PAFIO(PORT, N, PAL_LINE(IOPORTC, 8), AFIO_GPIO) | PAFIO(PORT, N, PAL_LINE(IOPORTB, 10), AFIO_GPIO) | PAFIO(PORT, N, PAL_LINE(IOPORTB, 11), AFIO_GPIO) | PAFIO(PORT, N, PAL_LINE(IOPORTB, 12), AFIO_GPIO) | 0)

#define PORT_SETUP(PORT)                    \
    {                                       \
        .DIR    = OUT_BITS(PORT),           \
        .INE    = IN_BITS(PORT),            \
        .PU     = IN_BITS(PORT),            \
        .PD     = 0x0000,                   \
        .OD     = 0x0000,                   \
        .DRV    = 0x0000,                   \
        .LOCK   = 0x0000,                   \
        .OUT    = OUT_BITS(PORT),           \
        .CFG[0] = AF_BITS(PORT, 0),         \
        .CFG[1] = AF_BITS(PORT, 1),         \
    }

const PALConfig pal_default_config = {
    .setup[0] = PORT_SETUP(IOPORTA),
    .setup[1] = PORT_SETUP(IOPORTB),
    .setup[2] = PORT_SETUP(IOPORTC),
    .setup[3] = PORT_SETUP(IOPORTD),
    .ESSR[0]  = 0x00000000,
    .ESSR[1]  = 0x00000000,
};

void __early_init(void) {
    ht32_clock_init();
}

void boardInit(void) {}
