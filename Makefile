all: kernel

kernel: kernel.o loader.o
	i586-elf-ld -T ./src/link.ld -o ./bin/kernel.bin ./bin/loader.o ./bin/kernel.o
	

loader.o: ./src/loader.s
	i586-elf-as -o ./bin/loader.o ./src/loader.s

kernel.o: ./src/kernel.c
	i586-elf-gcc -o ./bin/kernel.o -c ./src/kernel.c -Wall -Wextra \
				    -nostdlib -nostartfiles -nodefaultlibs

clean: 
	rm -f ./bin/*

install:
	losetup /dev/loop1 bin/floppy.img
	mount -t msdos /dev/loop1 /media/img
	cp ./bin/kernel.bin /media/img/kernel.bin
	umount /media/img
	losetup -d /dev/loop1
