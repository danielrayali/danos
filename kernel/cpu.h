#pragma once

#include "core/printer.h"
#include "core/types.h"

namespace danos {

extern "C" Bool IsCPUIDSupported();

void DumpRegisters(Printer* printer);

}  // namespace danos
