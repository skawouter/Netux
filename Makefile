all: kernel

kernel: kernel.o loader.o inter.o
	i586-elf-ld -T ./src/link.ld -o ./bin/kernel.bin ./bin/loader.o ./bin/kernel.o ./bin/console.o ./bin/inter.o  ./bin/interas.o
	

loader.o: ./src/loader.s
	i586-elf-as -o ./bin/loader.o ./src/loader.s

kernel.o: ./src/kernel.c
	i586-elf-gcc -o ./bin/kernel.o -c ./src/kernel.c -Wall -Wextra \
				    -nostdlib -nostartfiles -nodefaultlibs
	i586-elf-gcc -o ./bin/console.o -c ./src/console.c -Wall -Wextra \
				    -nostdlib -nostartfiles -nodefaultlibs

inter.o: ./src/inter.c
	i586-elf-gcc -o ./bin/inter.o -c ./src/inter.c -Wall -Wextra \
				    -nostdlib -nostartfiles -nodefaultlibs
	./nasm -f elf -o ./bin/interas.o ./src/inter.s
clean: 
	rm -f ./bin/*

install:
	losetup /dev/loop0 bin/floppy.img
	mount -t msdos /dev/loop0 /media/img
	cp ./bin/kernel.bin /media/img/kernel.bin
	umount /media/img
	losetup -d /dev/loop0
