#include "kernel/vga_text_buffer.h"
#include "kernel/multiboot_header.h"
#include "core/printer.h"
#include "kernel/bios_data.h"
#include "kernel/serial_port.h"
#include "kernel/programmable_interrupt_controller.h"
#include "kernel/interrupt_vector_table.h"
#include "kernel/cpu.h"

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

#if !defined(__i386__)
#error "This kernel needs to be compiled with a ix86-elf compiler"
#endif

using namespace danos;

extern "C" void kernel_main(void) {
    SerialPort serial_port;
    serial_port.Print("DanOS Bootloader v0.1.0 (Serial Port)\n");

    VgaTextBuffer vga_buffer(VgaColor::BLACK, VgaColor::LIGHT_GREEN);
    vga_buffer.Print("DanOS Bootloader v0.1.0 (VGA Text Buffer)\n");

    Bool cpuid_supported = IsCPUIDSupported();
    if (cpuid_supported) {
        vga_buffer.Print("CPUID command is supported\n");
    } else {
        vga_buffer.Print("CPUID command is not supported\n");
    }
}
