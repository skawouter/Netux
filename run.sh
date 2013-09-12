#!/bin/bash
qemu -fda bin/floppy.img -m 32 -drive file=./test.img,if=virtio
