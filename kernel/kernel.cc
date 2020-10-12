#include "vga_terminal.h"

extern "C" void init() {
    danos::VgaTerminal vga_terminal;
    vga_terminal.Print("Hello, World!");
    return;
}
