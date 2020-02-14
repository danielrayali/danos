all: build

build:
	i686-elf-as boot.s -o boot.o
	i686-elf-g++ -I../ -c vga_text_mode_buffer.cpp -o vga_text_mode_buffer.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti
	i686-elf-g++ -I../ -c kernel.cpp -o kernel.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti
	i686-elf-g++ -T linker.ld -o danos.bin -ffreestanding -O2 -nostdlib boot.o kernel.o vga_text_mode_buffer.o -lgcc
	cp danos.bin ../build/

clean:
	rm -rf *.o danos.bin
