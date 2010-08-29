CFLAGS = -Wall -Wextra -nostdlib -nostartfiles -nodefaultlibs -g
NASMFLAGS =  -f elf
CC = $(CC)
AS = /usr/cross/i586-elf/bin/i586-elf-as
NASM = ./nasm
LD = /usr/cross/i586-elf/bin/i586-elf-ld 
all: kernel

kernel: kernel.o loader.o desctbl.o isr.o irq.o keyb.o console.o desctblas.o interrupt.o
	$(LD) -T ./src/link.ld -o ./bin/kernel.bin $(.SOURCES)
	

loader.o: ./src/loader/loader.s
	$(AS) -o $(.TARGET) $(.SOURCE)

kernel.o: ./src/kernel.c
	 $(CC) -o $(.TARGET) -c $(.SOURCE) $(CFLAGS)

console.o: ./src/devices/console.c
	$(CC) -o $(.TARGET) -c $(.SOURCE) $(CFLAGS)

desctbl.o: ./src/init/desctbl.c 
	$(CC) -o $(.TARGET) -c $(.SOURCE) $(CFLAGS)

desctblas.o: ./src/init/desctbl.s
	$(NASM) $(NASMFLAGS) -o $(.TARGET)  $(.SOURCE)

interrupt.o: ./src/initinterrupt.s
	$(NASM) $(NASMFLAGS) -o $(.TARGET) $(.SOURCE)

isr.o: ./src/init/isr.c 
	$(CC) -o $(.TARGET) -c $(.SOURCE) $(CFLAGS)
		
irq.o: ./src/init/irq.c 
		$(CC) -o $(.TARGET) -c $(.SOURCE) $(CFLAGS)

keyb.o: ./src/devices/keyb.c
		$(CC) -o $(.TARGET) -c $(.SOURCE) $(CFLAGS)
					
clean: 
	rm -f ./bin/*.o
	rm -f ./bin/*.bin
	
recover:
	sudo umount /media/img
	sudo losetup -d /dev/loop1
	
install:
	losetup /dev/loop1 bin/floppy.img
	mount -t msdos /dev/loop1 /media/img
	cp ./bin/kernel.bin /media/img/kernel.bin
	umount /media/img
	losetup -d /dev/loop1
