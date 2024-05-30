#!/bin/bash
killall qemu-system-i386
qemu-system-i386 -fda bin/floppy.img -m 32 -enable-kvm -drive file=./test.img,if=ide,media=disk
