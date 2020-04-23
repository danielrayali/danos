#include "kernel/cpu.h"
#include "kernel/logging.h"
#include "core/string.h"
#include "kernel/io.h"
#include "kernel/keyboard_controller.h"

using namespace core;

namespace danos {

extern "C" Bool IsCPUIDSupported();
extern "C" Uint32 GetVendorIdString();
extern "C" Uint32 CheckA20();

inline void PrintValue(const Uint32 value, const Char* name) {
    Log(name);
    Log("=");
    Log(value);
    Log("\n");
}

void DumpRegisters() {
    Uint32 eax, ebx, ecx, edx;
    Uint32 esp, ebp, esi, edi;

    asm (
        "movl %%eax, %[a1] ;" "movl %%ebx, %[b1] ;" "movl %%ecx, %[c1] ;" "movl %%edx, %[d1] ;"
        "movl %%esp, %[a2] ;" "movl %%ebp, %[b2] ;" "movl %%esi, %[c2] ;" "movl %%edi, %[d2] ;"
        :
        [a1] "=m" (eax), [b1] "=m" (ebx), [c1] "=m" (ecx), [d1] "=m" (edx),
        [a2] "=m" (esp), [b2] "=m" (ebp), [c2] "=m" (esi), [d2] "=m" (edi)
    );

    PrintValue(eax, "eax");
    PrintValue(ebx, "ebx");
    PrintValue(ecx, "ecx");
    PrintValue(edx, "edx");

    PrintValue(esp, "esp");
    PrintValue(ebp, "ebp");
    PrintValue(esi, "esi");
    PrintValue(edi, "edi");
}

asm (
".global IsCPUIDSupported\n"
"IsCPUIDSupported:\n"
    "pushfl\n"
    "pushfl\n"
    "xorl $0x00200000, (%esp)\n"
    "popfl\n"
    "pushfl\n"
    "pop %eax\n"
    "xorl (%esp), %eax\n"
    "popfl\n"
    "andl $0x00200000, %eax\n"
    "shrl $21, %eax\n"              // Shift down to bit 0 for bool conversion
    "ret\n"
);

asm (
"# Function: check_a20"
"#"
"# Purpose: to check the status of the a20 line in a completely self-contained state-preserving way."
"#          The function can be modified as necessary by removing push's at the beginning and their"
"#          respective pop's at the end if complete self-containment is not required."
"#"
"# Returns: 0 in ax if the a20 line is disabled (memory wraps around)"
"#          1 in ax if the a20 line is enabled (memory does not wrap around)"
".global CheckA20\n"
"CheckA20:\n"
    "pushf\n"
    "push %ds\n"
    "push %es\n"
    "push %di\n"
    "push %si\n"
    "cli\n"
    "xor %ax, %ax # ax = 0\n"
    "mov %ax, %es\n"
    "not %ax # ax = 0xFFFF\n"
    "mov %ax, %ds\n"
    "mov $0x0500, %di\n"
    "mov $0x0510, %si\n"
    "movb %es:(%di), al\n"
    "push ax\n"
    "mov al, byte [ds:si]\n"
    "push ax\n"
    "mov byte [es:di], 0x00\n"
    "mov byte [ds:si], 0xFF\n"
    "cmp byte [es:di], 0xFF\n"
    "pop ax\n"
    "mov byte [ds:si], al\n"
    "pop ax\n"
    "mov byte [es:di], al\n"
    "mov ax, 0\n"
    "je check_a20__exit\n"
    "mov ax, 1\n"
"check_a20__exit:\n"
    "pop si\n"
    "pop di\n"
    "pop es\n"
    "pop ds\n"
    "popf\n"
    "ret\n"
);

bool CPU::Initialize() {
    if (!IsCPUIDSupported()) {
        Log("cpuid instruction not supported by the CPU\n");
        return true;
    }

    Uint32 ebx = 0, edx = 0, ecx = 0;
    asm (
        "mov $0, %%eax ;"
        "cpuid ;"
        "movl %%ebx, %[a1] ;" "movl %%edx, %[b1] ;" "movl %%ecx, %[c1] ;"
        :
        [a1] "=m" (ebx), [b1] "=m" (edx), [c1] "=m" (ecx)
    );

    Char vendor_id[13];
    *reinterpret_cast<Uint32*>(&vendor_id[0]) = ebx;
    *reinterpret_cast<Uint32*>(&vendor_id[4]) = edx;
    *reinterpret_cast<Uint32*>(&vendor_id[8]) = ecx;
    vendor_id[12] = '\0';

    Log("CPUID Vendor ID: ");
    Log(vendor_id);
    Log("\n");

    if (!String::Compare(vendor_id, "GenuineIntel")) {
        Log("DanOS is only built for CPUs with the \"GenuineIntel\" vendor ID\n");
        return true;
    }

    // Disable non-maskable interrupts and maskable interrupts
    IO::Out(0x70, IO::In(0x70) | 0x80);
    asm ("cli\n");

    // Check if A20 memory line has been enabled
    Uint32 a20_enabled = CheckA20();
    if (a20_enabled == 0) {
        // Enable A20 line
        KeyboardController::InitializeA20();
    }

    Log("A20 memory line has been enabled\n");

    // // Enter protected mode
    // asm (
    //     "cli\n"
    //     "lgdt (%gdtr)\n"
    // );

    return false;
}

}  // namespace danos
