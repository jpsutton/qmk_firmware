# MK Typist

Full-size wired keyboard (104 keys plus 4 media keys) built by Ducky for Mechanical Keyboards (PCB DK11-ONE02, a Ducky One 2 design), on a Holtek HT32F52352 (Cortex-M0+, 128 KB flash, LQFP64, marked HT50F52352).

* Keyboard Maintainer: [jpsutton](https://github.com/jpsutton)
* Hardware Supported: MK Typist (stock USB ID 04D9:0301)
* Hardware Availability: [mechanicalkeyboards.com](https://mechanicalkeyboards.com/products/mk-typist)

This port keeps the stock IAP bootloader. The firmware is linked at 0x3200, right after the bootloader (0x0000-0x2FFF) and its version page (0x3000-0x31FF).

Make example for this keyboard (after setting up your build environment):

    make mk/typist:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the stock IAP bootloader (04D9:1301) in one of these ways:

* **Bootmagic reset**: hold Esc while plugging in the keyboard
* **Keycode in layout**: press the key mapped to `QK_BOOT` if it is available

Flashing through the stock IAP needs a tool that speaks its update protocol. This is not wired up yet.
