#include "vga_terminal.h"
#include "types.h"

namespace danos {

VgaTerminal::VgaTerminal() : vga_buffer_(VgaBuffer::Color::LIGHT_GREEN, VgaBuffer::Color::BLACK) { }

void VgaTerminal::Print(const char* message) {
    for (UInt32 i = 0; message[i] != '\0'; i++) {
        vga_buffer_.Put(message[i]);
    }
}

    
}  // namespace danos
