# MK Typist

![MK Typist PCB](https://raw.githubusercontent.com/jpsutton/mk-typist-research/main/photos/2026-10-24_pcb-bottom_mcu-area-overview.jpg)

Full-size wired keyboard (104 keys plus Calculator, Mute and volume keys) built by Ducky for Mechanical Keyboards, on a Ducky One 2 PCB (DK11-ONE02) with a Holtek HT32F52352. The firmware runs on the keyboard's stock bootloader, which stays in place.

* Keyboard Maintainer: [Jared Sutton](https://github.com/jpsutton)
* Hardware Supported: MK Typist PCB DK11-ONE02, HT32F52352 (stock firmware USB ID 04D9:0301)
* Hardware Availability: [mechanicalkeyboards.com](https://mechanicalkeyboards.com/products/mk-typist)

Make example for this keyboard (after setting up your build environment):

    make mk/typist:default

Flashing example for this keyboard:

    cykb.py flash mk_typist_default.bin <version-page.bin>

`make mk/typist:default:flash` only prints a pointer to that tool and stops. The stock bootloader uses the Cheng Yong "CYKB" HID update protocol, which no QMK flashing tool speaks. Use `cykb.py` from [mk-typist-tools](https://github.com/jpsutton/mk-typist-tools). It extracts the required version page from the vendor updater and checks the image before writing. Its README has the full steps. Hardware details and recovery options are in [mk-typist-research](https://github.com/jpsutton/mk-typist-research).

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the stock bootloader (USB ID 04D9:1301) in 3 ways:

* **Bootmagic reset**: Hold down Escape and plug in the keyboard
* **Keycode in layout**: Press Fn+Escape (`QK_BOOT` on layer 1 of the default keymap)
* **From the stock firmware**: Run `cykb.py reboot-bl`
