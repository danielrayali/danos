#pragma once

#include "terminal.h"
#include "types.h"

namespace danos {

void SetTerminal(Terminal* terminal);

void KPrint(const char* message);

/* Prints a single value on its own line */
void KPrint(const UInt32 value);

/* Prints a single value on its own line */
void KPrint(const UInt64 value);

}  // namespace danos
