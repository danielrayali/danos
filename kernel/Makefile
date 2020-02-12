all: build

build:
	i686-elf-as boot.s -o boot.o
	i686-elf-g++ -c kernel.cpp -o kernel.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti
	# i686-elf-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-g++ -T linker.ld -o danos.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc
	cp danos.bin ../build/

clean:
	rm -rf *.o danos.bin
