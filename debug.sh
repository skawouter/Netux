#!/bin/bash
qemu -s -S -fda bin/floppy.img -m 32 &
sleep 2
xvncviewer localhost:5900 &
gdb
