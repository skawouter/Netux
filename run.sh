#!/bin/bash
killall qemu-system-i386
../qemu/i386-softmmu/qemu-system-i386 -fda bin/floppy.img -m 32 -enable-kvm -sdl -drive file=./test.img,if=ide,media=disk
