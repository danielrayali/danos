#pragma once

#include "core/printer.h"

namespace danos {

extern "C" bool IsCPUIDSupported();

void DumpRegisters(Printer* printer);

}  // namespace danos
