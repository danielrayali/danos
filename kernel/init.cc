#include "kprint.h"
#include "vga_terminal.h"
#include "global_descriptor_table.h"

using namespace danos;

static GlobalDescriptorTable gdt;

extern "C" void init() {
    // Setup VGA terminal for KPrint
    VgaTerminal vga_terminal;
    SetTerminal(&vga_terminal);
    KPrint("DanOS VGA Terminal Initialized\n");
    KPrint("Attempting to KPrint() 1234\n");
    KPrint((UInt32)1234);
    KPrint("Attempting to KPrint() 2482716212\n");
    KPrint((UInt32)2482716212);
    KPrint("Attempting to KPrint() 5858742948482716245\n");
    KPrint((UInt64)5858742948482716245);
    KPrint("Attempting to KPrint() 0xA1B2C3D4\n");
    UInt32 value = 0xA1B2C3D4;
    KPrint((UInt8*)&value, 4);
    KPrint("\n");

    KPrint("Verifying Multiboot header lives at 0x100000...\n");
    UInt32 *multiboot_magic = (UInt32*)0x100000;
    const UInt32 kMultibootMagic = 0x1BADB002;
    if (*multiboot_magic != kMultibootMagic) {
        KPrint("Multiboot image verification failed\n");
        return;
    }
    KPrint("Multiboot image verified\n");

    return;
}
