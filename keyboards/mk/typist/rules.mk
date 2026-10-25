# MCU: Holtek HT32F52352 (Cortex-M0+, 128 KB flash, 16 KB SRAM), LQFP64.
# The chip is marked "HT50F52352" like other Holtek keyboard parts.
MCU = cortex-m0plus
ARMV = 6
USE_FPU = no
MCU_FAMILY = HT32
MCU_SERIES = HT32F523xx
MCU_LDSCRIPT = HT32F52352_MK_TYPIST
MCU_STARTUP = ht32f523xx

BOARD = HT_HT32F52342_52

# The stock Cheng Yong IAP bootloader (04D9:1301) stays in place below 0x3000.
BOOTLOADER = custom

# The app must start exactly at 0x3200 (see ld/HT32F52352_MK_TYPIST.ld), and
# sets VTOR itself instead of relying on the IAP to do it.
EXTRALDFLAGS = -Wl,--defsym=__vectors_align__=512
OPT_DEFS += -DCRT0_VTOR_INIT=TRUE

# Indicator LEDs (MBI5042)
SRC += mbi5042.c
