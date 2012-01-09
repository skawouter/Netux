#!/bin/bash
killall qemu
qemu -fda bin/floppy.img -m 32 -net tap -net nic,model=rtl8139,macaddr=ab:cd:ef:21:43:65 &
