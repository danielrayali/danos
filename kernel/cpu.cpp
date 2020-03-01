#include "kernel/cpu.h"

namespace danos {

inline void PrintValue(const Uint32 value, const Char* name, Printer* printer) {
    printer->Print(name);
    printer->Print("=");
    PrintUint32(*printer, value);
    printer->Print("\n");
}

void DumpRegisters(Printer* printer) {
    Uint32 eax, ebx, ecx, edx;
    Uint32 esp, ebp, esi, edi;

    asm (
        "movl %%eax, %[a1] ;" "movl %%ebx, %[b1] ;" "movl %%ecx, %[c1] ;" "movl %%edx, %[d1] ;"
        "movl %%esp, %[a2] ;" "movl %%ebp, %[b2] ;" "movl %%esi, %[c2] ;" "movl %%edi, %[d2] ;"
        :
        [a1] "=m" (eax), [b1] "=m" (ebx), [c1] "=m" (ecx), [d1] "=m" (edx),
        [a2] "=m" (esp), [b2] "=m" (ebp), [c2] "=m" (esi), [d2] "=m" (edi)
    );

    PrintValue(eax, "eax", printer);
    PrintValue(ebx, "ebx", printer);
    PrintValue(ecx, "ecx", printer);
    PrintValue(edx, "edx", printer);

    PrintValue(esp, "esp", printer);
    PrintValue(ebp, "ebp", printer);
    PrintValue(esi, "esi", printer);
    PrintValue(edi, "edi", printer);
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

}  // namespace danos
