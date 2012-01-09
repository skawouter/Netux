CFLAGS = -Wall -Wextra -nostdlib -nostartfiles -nodefaultlibs -g -mtune=i386 -march=i386 -m32
NASMFLAGS = -f elf
CC = gcc 
NASM = nasm
LD = ld
LDFLAGS = -melf_i386
BIN = ./bin/
HEADER = ./src/include/
DEVDIR = ./src/devices/
LOADDIR = ./src/loader/
INITDIR = ./src/init/
SRCDIR = ./src/
MODULES = kernel.o loader.o desctbl.o isr.o irq.o keyb.o console.o desctblas.o interrupt.o devices.o pci.o math.o mm.o mmas.o
all: kernel

kernel: $(MODULES)
	$(LD) $(LDFLAGS) -T ./src/link.ld -o $(BIN)kernel.bin $(MODULES:%=$(BIN)%)

pci.o: $(DEVDIR)pci.c
	$(CC) -o $(BIN)$@ -c $? $(CFLAGS)

loader.o: $(LOADDIR)loader.s
	$(NASM) $(NASMFLAGS) -o $(BIN)$@ $?

kernel.o: $(SRCDIR)kernel.c
	$(CC) -o $(BIN)$@ -c $? $(CFLAGS)

math.o: $(SRCDIR)math.c
	$(CC) -o $(BIN)$@ -c $? $(CFLAGS)

console.o: $(DEVDIR)console.c
	$(CC) -o $(BIN)$@ -c $? $(CFLAGS)

desctbl.o: $(INITDIR)desctbl.c 
	$(CC) -o $(BIN)$@ -c $? $(CFLAGS)

desctblas.o: $(INITDIR)desctbl.s
	$(NASM) $(NASMFLAGS) -o $(BIN)$@ $?

interrupt.o: $(INITDIR)interrupt.s
	$(NASM) $(NASMFLAGS) -o $(BIN)$@ $?

isr.o: $(INITDIR)isr.c 
	$(CC) -o $(BIN)$@ -c $? $(CFLAGS)
	
irq.o: $(INITDIR)irq.c 
	$(CC) -o $(BIN)$@ -c $? $(CFLAGS)

keyb.o: $(DEVDIR)keyb.c
	$(CC) -o $(BIN)$@ -c $? $(CFLAGS)

devices.o: $(DEVDIR)device.c
	$(CC) -o $(BIN)$@ -c $? $(CFLAGS)
	
mm.o: $(INITDIR)mm.c 
	$(CC) -o $(BIN)$@ -c $? $(CFLAGS)

mmas.o: $(INITDIR)mm.s
	$(NASM) $(NASMFLAGS) -o $(BIN)$@ $? 

clean: 
	rm -f $(BIN).o
	rm -f $(BIN).bin

recover:
	sudo umount /media/img
	sudo losetup -d /dev/loop1

install:
	losetup /dev/loop1 $(BIN)floppy.img
	mount -t msdos /dev/loop1 /media/img
	cp $(BIN)kernel.bin /media/img/kernel.bin
	umount /media/img
	losetup -d /dev/loop1
