all: kernel

kernel: kernel.o loader.o desctbl.o isr.o
	/usr/cross/i586-elf/bin/i586-elf-ld -T ./src/link.ld -o ./bin/kernel.bin ./bin/loader.o ./bin/kernel.o ./bin/console.o ./bin/desctbl.o  ./bin/desctblas.o ./bin/interrupt.o ./bin/isr.o
	

loader.o: ./src/loader.s
	/usr/cross/i586-elf/bin/i586-elf-as -o ./bin/loader.o ./src/loader.s

kernel.o: ./src/kernel.c
	/usr/cross/i586-elf/bin/i586-elf-gcc -o ./bin/kernel.o -c ./src/kernel.c -Wall -Wextra \
				    -nostdlib -nostartfiles -nodefaultlibs -g
	/usr/cross/i586-elf/bin/i586-elf-gcc -o ./bin/console.o -c ./src/console.c -Wall -Wextra \
				    -nostdlib -nostartfiles -nodefaultlibs -g

desctbl.o: ./src/desctbl.c ./src/desctbl.s
	/usr/cross/i586-elf/bin/i586-elf-gcc -o ./bin/desctbl.o -c ./src/desctbl.c -Wall -Wextra \
				    -nostdlib -nostartfiles -nodefaultlibs -g
	./nasm -f elf -o ./bin/desctblas.o ./src/desctbl.s
	
isr.o: ./src/isr.c ./src/interrupt.s
		/usr/cross/i586-elf/bin/i586-elf-gcc -o ./bin/isr.o -c ./src/isr.c -Wall -Wextra \
				    -nostdlib -nostartfiles -nodefaultlibs -g
		./nasm -f elf -o ./bin/interrupt.o ./src/interrupt.s
clean: 
	rm -f ./bin/*.o
	rm -f ./bin/*.bin

install:
	losetup /dev/loop1 bin/floppy.img
	mount -t msdos /dev/loop1 /media/img
	cp ./bin/kernel.bin /media/img/kernel.bin
	umount /media/img
	losetup -d /dev/loop1
