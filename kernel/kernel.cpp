#include "kernel/vga_text_buffer.h"
#include "kernel/multiboot_header.h"
#include "core/printer.h"
#include "kernel/bios_data.h"
#include "kernel/serial_port.h"

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

#if !defined(__i386__)
#error "This kernel needs to be compiled with a ix86-elf compiler"
#endif

using namespace danos;

extern "C" void kernel_main(void) {
    VgaTextBuffer vga_text_buffer(VgaColor::BLACK, VgaColor::LIGHT_GREEN);
    vga_text_buffer.Print("DanOS Bootloader v0.1.0 (VGA)\n\n");

    MultibootHeader *multiboot_header = reinterpret_cast<MultibootHeader*>(0x100000);
    PrintMultibootHeader(vga_text_buffer, multiboot_header);

    SerialPort serial_port;
    serial_port.Print("DanOS Bootloader v0.1.0 (serial)\n");
}
