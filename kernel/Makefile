OBJS = kernel.o \
	vga_buffer.o \
	kprint.o \
	abi.o \
	vga_terminal.o
#	vga_text_buffer.o \
#	kernel.o \
#	bios_data.o \
#	serial_port.o \
#	programmable_interrupt_controller.o \
#	interrupt_vector_table.o \
#	cpu.o \
#	logging.o \
#	../core/string.o  # TODO(dali) Create actual core library and link to kernel

CC=../build/toolchain/opt/local/bin/i686-elf-gcc
AS=../build/toolchain/opt/local/bin/i686-elf-as
CXX=../build/toolchain/opt/local/bin/i686-elf-g++
CXXFLAGS=-I.. -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -nostdlib -std=c++11 -masm=att

all: ../build/danos.bin

%.o: %.cc
	$(CC) -c -o $@ $< $(CFLAGS) $(CXXFLAGS)

../build/danos.bin: $(OBJS)
	$(AS) boot.s -o boot.o
	$(CXX) -T linker.ld -o $@ -ffreestanding -O2 -nostdlib boot.o $(OBJS) -lgcc

clean:
	rm -rf *.o danos.bin ../build/danos.bin

