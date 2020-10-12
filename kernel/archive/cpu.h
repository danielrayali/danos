#pragma once

#include "core/printer.h"
#include "core/types.h"

namespace danos {

class CPU {
 public:
    // Prints the current values of the registers in the CPU
    static void DumpRegisters();

    // Gets the current address of the top of the stack
    static Uint32 GetStackAddress();

    // Initializes the CPU. Returns true if an error occured
    static bool Initialize();
};

}  // namespace danos
