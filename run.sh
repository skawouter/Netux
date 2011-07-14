#!/bin/bash
killall qemu
qemu -fda bin/floppy.img -m 32 -net nic,model=rtl8139 &
