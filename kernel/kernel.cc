#include "kprint.h"
#include "vga_terminal.h"

extern "C" void init() {
    // Setup VGA terminal for KPrint
    danos::VgaTerminal vga_terminal;
    danos::SetTerminal(&vga_terminal);
    danos::KPrint("DanOS VGA Terminal Initialized\n");
    return;
}
