#pragma once

#include "core/types.h"
#include "core/printer.h"

namespace danos {

void Log(const Char character);

void Log(const Char* message);

void Log(const Uint32 value);

void SetLogger(Printer* printer);

}  // namespace danos
