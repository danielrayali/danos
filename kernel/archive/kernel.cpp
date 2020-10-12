#include "kernel/vga_text_buffer.h"
#include "kernel/cpu.h"
#include "kernel/logging.h"

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

#if !defined(__i386__)
#error "This kernel needs to be compiled with a ix86-elf compiler"
#endif

using namespace danos;

extern "C" void kernel_main(void) {
    // Setup logging
    VgaTextBuffer vga_buffer(VgaColor::BLACK, VgaColor::LIGHT_GREEN);
    SetLogger(&vga_buffer);
    Log("DanOS Bootloader v0.1.0 (VGA Text Buffer)\n");

    Log("Initializing CPU...\n");
    if (CPU::Initialize()) {
        Log("Error initializing the CPU, kernel exiting\n");
        return;
    } else {
        Log("CPU initialized\n");
    }
}
