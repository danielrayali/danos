#include "kernel/cpu.h"

namespace danos {

void DumpRegisters(Printer* printer) {
    uint32_t eax32, ebx32, ecx32, edx32;
    uint64_t rax64, rbx64, rcx64, rdx64;

    asm (
        "movl %%eax, %[a1] ;"
        "movl %%ebx, %[b1] ;"
        "movl %%ecx, %[c1] ;"
        "movl %%edx, %[d1] ;"
        "movq %%rax, %[a2] ;"
        "movq %%rbx, %[b2] ;"
        "movq %%rcx, %[c2] ;"
        "movq %%rdx, %[d2] ;"
        :
        [a1] "=m" (eax32),
        [b1] "=m" (ebx32),
        [c1] "=m" (ecx32),
        [d1] "=m" (edx32),
        [a2] "=m" (rax64), [b2] "=m" (rbx64), [c2] "=m" (rcx64), [d2] "=m" (rdx64)
    );

    printer->Print("eax=");
    PrintUint32(*printer, eax32);
    printer->Print("\n");
    printer->Print("ebx=");
    PrintUint32(*printer, ebx32);
    printer->Print("\n");
    printer->Print("ecx=");
    PrintUint32(*printer, ecx32);
    printer->Print("\n");
    printer->Print("edx=");
    PrintUint32(*printer, edx32);
    printer->Print("\n");

}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreturn-type"
bool IsCPUIDSupported() {
    asm (
        "pushfl\n"
        "pushfl\n"
        "push %edx\n"
        "movl $200000, %edx\n"
        "xor %edx, (%esp)\n"
        "popl %edx\n"
        "popfl\n"
        "pushfl\n"
        "pop %eax\n"
        "xor (%esp), %eax\n"
        "popfl\n"
        "and $200000, %eax\n"
        "ret\n"
    );
}
#pragma GCC diagnostic pop

}  // namespace danos
