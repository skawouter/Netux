CFLAGS = -Wall -Wextra -nostdlib -nostartfiles -nodefaultlibs -g
NASMFLAGS =  -f elf
CC = /usr/cross/i586-elf/bin/i586-elf-gcc
AS = /usr/cross/i586-elf/bin/i586-elf-as
NASM = ./nasm
LD = /usr/cross/i586-elf/bin/i586-elf-ld
BIN = ./bin/
all: kernel

kernel: kernel.o loader.o desctbl.o isr.o irq.o keyb.o console.o desctblas.o interrupt.o devices.o pci.o math.o mm.o
	$(LD) -T ./src/link.ld -o  $(BIN)kernel.bin $(BIN)kernel.o $(BIN)loader.o $(BIN)desctbl.o $(BIN)isr.o $(BIN)irq.o $(BIN)keyb.o $(BIN)console.o $(BIN)desctblas.o $(BIN)interrupt.o $(BIN)devices.o $(BIN)pci.o $(BIN)math.o $(BIN)mm.o $(BIN)mmas.o

pci.o: ./src/devices/pci.c
	$(CC) -o $(BIN)pci.o  -c ./src/devices/pci.c $(CFLAGS)

loader.o: ./src/loader/loader.s
	$(AS) -o $(BIN)loader.o ./src/loader/loader.s

kernel.o: ./src/kernel.c
	 $(CC) -o $(BIN)kernel.o -c ./src/kernel.c $(CFLAGS)

math.o: ./src/math.c
	$(CC) -o $(BIN)math.o -c ./src/math.c $(CFLAGS)

console.o: ./src/devices/console.c
	$(CC) -o $(BIN)console.o -c ./src/devices/console.c $(CFLAGS)

desctbl.o: ./src/init/desctbl.c
	$(CC) -o $(BIN)desctbl.o -c ./src/init/desctbl.c $(CFLAGS)

desctblas.o: ./src/init/desctbl.s
	$(NASM) $(NASMFLAGS) -o $(BIN)desctblas.o  ./src/init/desctbl.s

interrupt.o: ./src/init/interrupt.s
	$(NASM) $(NASMFLAGS) -o $(BIN)interrupt.o ./src/init/interrupt.s

isr.o: ./src/init/isr.c
	$(CC) -o $(BIN)isr.o -c ./src/init/isr.c $(CFLAGS)

irq.o: ./src/init/irq.c
		$(CC) -o $(BIN)irq.o -c ./src/init/irq.c $(CFLAGS)

keyb.o: ./src/devices/keyb.c
		$(CC) -o $(BIN)keyb.o -c ./src/devices/keyb.c $(CFLAGS)
devices.o: ./src/devices/device.c
		$(CC) -o $(BIN)devices.o -c ./src/devices/device.c $(CFLAGS)
mm.o: ./src/init/mm.c ./src/init/mm.s
		$(CC) -o $(BIN)mm.o -c ./src/init/mm.c $(CFLAGS)
		$(NASM) $(NASMFLAGS) -o $(BIN)mmas.o ./src/init/mm.s
clean:
	rm -f $(BIN)*.o
	rm -f $(BIN)*.bin

recover:
	sudo umount /media/img
	sudo losetup -d /dev/loop1

install:
	losetup /dev/loop1 $(BIN)floppy.img
	mount -t msdos /dev/loop1 /media/img
	cp $(BIN)kernel.bin /media/img/kernel.bin
	umount /media/img
	losetup -d /dev/loop1
