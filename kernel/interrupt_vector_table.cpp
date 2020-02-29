#include "interrupt_vector_table.h"

namespace danos {

static Printer* g_printer;

void KeyboardInterrupt() {
    g_printer->Print("KeyboardInterrupt fired");
}

void InterruptVectorTable::Initialize(Printer& printer) {
    g_printer = &printer;

    // Set up the keyboard interrupt
    Uint32 address = reinterpret_cast<Uint32>(&KeyboardInterrupt);
    printer.Print("Setting 0x0024 to ");
    PrintUint32(printer, address);

    Uint32* keyboard_interrupt = reinterpret_cast<Uint32*>(0x0024);
    *keyboard_interrupt = address;
}

}  // namespace danos
