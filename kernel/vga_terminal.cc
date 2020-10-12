#include "vga_terminal.h"

namespace danos {

VgaTerminal::VgaTerminal() {
    vga_buffer_.Clear();
}

void VgaTerminal::Print(const char letter) {
    vga_buffer_.SetByte(position_++, letter);
}

void VgaTerminal::Print(const char* string, const UInt64 size) {
    for (UInt64 i = 0; i < size; ++i) {
        this->Print(string[i]);
    }
}

void VgaTerminal::Print(const char* string) {
    for (UInt64 i = 0; string[i] != '\0'; ++i) {
        this->Print(string[i]);
    }
}

}  // namespace danos
