/*
    ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/*
 * HT32F52352 with the MK Typist stock IAP bootloader.
 * 0x0000-0x2FFF IAP, 0x3000-0x31FF version page, application from 0x3200.
 * The last word of SRAM holds the IAP magic and is kept out of the image.
 * The IAP reads a 12-byte application header at 0x3BF8: it only jumps to the
 * application if the first word is 0x04040000, and its checksum command needs
 * the second. See docs/stock-iap.md in
 * https://github.com/jpsutton/mk-typist-research Flash is split around it: flash0 holds
 * the vector table, flash1 the header, flash2 everything else.
 */
MEMORY {
    flash0  : org = 0x00003200, len = 0x3BF8 - 0x3200
    flash1  : org = 0x00003BF8, len = 12
    flash2  : org = 0x00003C04, len = 127k + 512 - 0x3C04  /* 127.5 KB main flash */
    flash3  : org = 0x00000000, len = 0
    flash4  : org = 0x00000000, len = 0
    flash5  : org = 0x00000000, len = 0
    flash6  : org = 0x00000000, len = 0
    flash7  : org = 0x00000000, len = 0
    ram0    : org = 0x20000000, len = 16k - 4
    ram1    : org = 0x00000000, len = 0
    ram2    : org = 0x00000000, len = 0
    ram3    : org = 0x00000000, len = 0
    ram4    : org = 0x00000000, len = 0
    ram5    : org = 0x00000000, len = 0
    ram6    : org = 0x00000000, len = 0
    ram7    : org = 0x00000000, len = 0
}

/* For each data/text section two region are defined, a virtual region
   and a load region (_LMA suffix).*/

/* Flash region to be used for exception vectors.*/
REGION_ALIAS("VECTORS_FLASH", flash0);
REGION_ALIAS("VECTORS_FLASH_LMA", flash0);

/* Flash region to be used for constructors and destructors.*/
REGION_ALIAS("XTORS_FLASH", flash2);
REGION_ALIAS("XTORS_FLASH_LMA", flash2);

/* Flash region to be used for code text.*/
REGION_ALIAS("TEXT_FLASH", flash2);
REGION_ALIAS("TEXT_FLASH_LMA", flash2);

/* Flash region to be used for read only data.*/
REGION_ALIAS("RODATA_FLASH", flash2);
REGION_ALIAS("RODATA_FLASH_LMA", flash2);

/* Flash region to be used for various.*/
REGION_ALIAS("VARIOUS_FLASH", flash2);
REGION_ALIAS("VARIOUS_FLASH_LMA", flash2);

/* Flash region to be used for RAM(n) initialization data.*/
REGION_ALIAS("RAM_INIT_FLASH_LMA", flash2);

/* RAM region to be used for Main stack. This stack accommodates the processing
   of all exceptions and interrupts.*/
REGION_ALIAS("MAIN_STACK_RAM", ram0);

/* RAM region to be used for the process stack. This is the stack used by
   the main() function.*/
REGION_ALIAS("PROCESS_STACK_RAM", ram0);

/* RAM region to be used for data segment.*/
REGION_ALIAS("DATA_RAM", ram0);
REGION_ALIAS("DATA_RAM_LMA", flash2);

/* RAM region to be used for BSS segment.*/
REGION_ALIAS("BSS_RAM", ram0);

/* RAM region to be used for the default heap.*/
REGION_ALIAS("HEAP_RAM", ram0);

/* The application must start exactly at 0x3200, where the IAP jumps. The
   vector table (48 entries, 192 bytes) needs far less than the ChibiOS
   default of 1024-byte alignment, so rules.mk sets
   --defsym=__vectors_align__=512.*/

/* Generic rules inclusion.*/
INCLUDE rules.ld

SECTIONS
{
    .iap_header :
    {
        KEEP(*(.iap_header))
    } > flash1
}
