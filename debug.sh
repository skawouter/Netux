#!/bin/bash
qemu -s -S -d int -fda bin/floppy.img -m 32 -net nic,model=rtl8139 &
sleep 2
xvncviewer localhost:5900 &
gdb


#0424250
