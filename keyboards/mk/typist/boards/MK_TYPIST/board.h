// Copyright 2026 Jared Sutton (@jpsutton)
// SPDX-License-Identifier: Apache-2.0

#pragma once

#define BOARD_NAME "MK Typist"

#define HT32F52352

#define HT32_LSECLK 32768
#define HT32_HSECLK 8000000

#define FLASH_SIZE (0x1FE00 - 0x3200) // 127.5 KB main flash minus IAP and version page

#if !defined(_FROM_ASM_)
#    ifdef __cplusplus
extern "C" {
#    endif
void boardInit(void);
#    ifdef __cplusplus
}
#    endif
#endif /* _FROM_ASM_ */
