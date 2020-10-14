#include "io.h"

namespace danos {

void IO::Out(UInt16 port, UInt8 value) {
    asm volatile("outb %0, %1" ::"a"(value), "Nd"(port));
}

}  // namespace danos
