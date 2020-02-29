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
    VgaTextBuffer vga_buffer(VgaColor::BLACK, VgaColor::LIGHT_GREEN);
    serial_port.Print("DanOS Bootloader v0.1.0 (VGA Text Buffer)\n");

    SerialPort serial_port;
    serial_port.Print("DanOS Bootloader v0.1.0 (Serial Port)\n");

    vga_buffer.Print("Prior to CPUID\n");
    DumpRegisters(&vga_buffer);
    // const bool cpuid_supported = IsCPUIDSupported();
    // if (cpuid_supported) {
    //     serial_port.Print("CPUID command is supported");
    // } else {
    //     serial_port.Print("CPUID command is not supported");
    // }
    // vga_buffer.Print("After CPUID\n");
    // DumpRegisters(&vga_buffer);
}
