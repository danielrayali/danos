OBJS = init.o \
	vga_buffer.o \
	kprint.o \
	abi.o \
	vga_terminal.o \
	io.o \
	global_descriptor_table.o \
	crt0.o \
	crti.o \
	crtn.o

CC=../build/toolchain/opt/local/bin/i686-elf-gcc
AS=../build/toolchain/opt/local/bin/i686-elf-as
CXX=../build/toolchain/opt/local/bin/i686-elf-g++
CXXFLAGS=-I.. -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -nostdlib -std=c++11 -masm=att -m64

CRTI_OBJ=crti.o
CRTBEGIN_OBJ:=$(shell $(CC) $(CFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ:=$(shell $(CC) $(CFLAGS) -print-file-name=crtend.o)
CRTN_OBJ=crtn.o
OBJS+=$(CRTI_OBJ) $(CRTBEGIN_OBJ) $(CRTEND_OBJ) $(CRTN_OBJ)

all: ../build/danos.bin

%.o: %.cc
	$(CC) -c -o $@ $< $(CFLAGS) $(CXXFLAGS)

../build/danos.bin: $(OBJS)
	$(AS) boot.s -o boot.o
	$(CXX) -T linker.ld -o $@ -ffreestanding -O2 -nostdlib boot.o $(OBJS) -lgcc

clean:
	rm -rf *.o danos.bin ../build/danos.bin

