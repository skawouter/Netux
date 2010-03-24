all: kernel

kernel: kernel.o loader.o desctbl.o isr.o
	i586-elf-ld -T ./src/link.ld -o ./bin/kernel.bin ./bin/loader.o ./bin/kernel.o ./bin/console.o ./bin/desctbl.o  ./bin/desctblas.o ./bin/interrupt.o ./bin/isr.o
	

loader.o: ./src/loader.s
	i586-elf-as -o ./bin/loader.o ./src/loader.s

kernel.o: ./src/kernel.c
	i586-elf-gcc -o ./bin/kernel.o -c ./src/kernel.c -Wall -Wextra \
				    -nostdlib -nostartfiles -nodefaultlibs
	i586-elf-gcc -o ./bin/console.o -c ./src/console.c -Wall -Wextra \
				    -nostdlib -nostartfiles -nodefaultlibs

desctbl.o: ./src/desctbl.c ./src/desctbl.s
	i586-elf-gcc -o ./bin/desctbl.o -c ./src/desctbl.c -Wall -Wextra \
				    -nostdlib -nostartfiles -nodefaultlibs
	./nasm -f elf -o ./bin/desctblas.o ./src/desctbl.s
	
isr.o: ./src/isr.c ./src/interrupt.s
		i586-elf-gcc -o ./bin/isr.o -c ./src/isr.c -Wall -Wextra \
				    -nostdlib -nostartfiles -nodefaultlibs
		./nasm -f elf -o ./bin/interrupt.o ./src/interrupt.s
clean: 
	rm -f ./bin/*.o
	rm -f ./bin/*.bin

install:
	losetup /dev/loop0 bin/floppy.img
	mount -t msdos /dev/loop0 /media/img
	cp ./bin/kernel.bin /media/img/kernel.bin
	umount /media/img
	losetup -d /dev/loop0
