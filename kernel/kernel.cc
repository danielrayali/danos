#include "vga_buffer.h"

using namespace danos;

extern "C" void init() {
    danos::VgaBuffer vga_buffer;
    vga_buffer.SetByte(0, 'H');
    vga_buffer.SetByte(1, 'e');
    vga_buffer.SetByte(2, 'l');
    vga_buffer.SetByte(3, 'l');
    vga_buffer.SetByte(4, 'o');
    return;
}
