#include "kprint.h"
#include "vga_terminal.h"

extern "C" void init() {
    // Setup VGA terminal for KPrint
    danos::VgaTerminal vga_terminal;
    danos::SetTerminal(&vga_terminal);
    danos::KPrint("DanOS VGA Terminal Initialized\n");
    danos::KPrint("Attempting to KPrint() 1234\n");
    danos::KPrint((danos::UInt32)1234);
    danos::KPrint("Attempting to KPrint() 2482716212\n");
    danos::KPrint((danos::UInt32)2482716212);
    danos::KPrint("Attempting to KPrint() 5858742948482716245\n");
    danos::KPrint((danos::UInt64)5858742948482716245);
    return;
}
