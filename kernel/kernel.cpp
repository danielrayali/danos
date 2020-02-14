#include "vga_text_mode_buffer.h"

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

#if !defined(__i386__)
#error "This kernel needs to be compiled with a ix86-elf compiler"
#endif

using namespace danos;

char ToHex(unsigned value) {
    if (value < 10) {
        return ('0' + value);
    } else {
        return ('a' + (value - 10));
    }
}

void PrintUint32(VgaTextModeBuffer& buffer, Uint32* value) {
    buffer.Print('0');
    buffer.Print('x');
    Uint8* value_ptr = (Uint8*)value;
    for (int i = 3; i >= 0; --i) {
        buffer.Print(ToHex(value_ptr[i] >> 4));
        buffer.Print(ToHex(value_ptr[i] & 0xF));
    }
}

extern "C" void kernel_main(void) {
    VgaTextModeBuffer vga_buffer(VgaColor::BLACK, VgaColor::LIGHT_GREEN);
    vga_buffer.Print("Hello, World!\n", 14);

    vga_buffer.Print("Address 0x100000: ", 18);
    PrintUint32(vga_buffer, (Uint32*)0x100000);
}
