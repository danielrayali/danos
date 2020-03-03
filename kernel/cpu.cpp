#include "kernel/cpu.h"
#include "kernel/logging.h"
#include "core/string.h"

using namespace core;

namespace danos {

extern "C" Bool IsCPUIDSupported();
extern "C" Uint32 GetVendorIdString();

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

    Log("CPU Vendor ID: ");
    Log(vendor_id);
    Log("\n");

    if (!String::Compare(vendor_id, "GenuineIntel")) {
        Log("DanOS is only built for CPUs with the \"GenuineIntel\" vendor ID\n");
        return true;
    }

    return false;
}

}  // namespace danos
