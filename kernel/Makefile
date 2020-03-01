OBJS = \
	vga_text_buffer.o \
	kernel.o \
	bios_data.o \
	serial_port.o \
	programmable_interrupt_controller.o \
	interrupt_vector_table.o \
	cpu.o

CC=../build/toolchain/opt/local/bin/i686-elf-gcc
CXXFLAGS=-I.. -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -nostdlib -std=c++11 -masm=att

all: ../build/danos.bin

%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS) $(CXXFLAGS)

../build/danos.bin: $(OBJS)
	i686-elf-as boot.s -o boot.o
	i686-elf-g++ -T linker.ld -o $@ -ffreestanding -O2 -nostdlib boot.o $(OBJS) -lgcc

clean:
	rm -rf *.o danos.bin ../build/danos.bin
