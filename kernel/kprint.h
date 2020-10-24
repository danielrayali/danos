#pragma once

#include "terminal.h"
#include "types.h"

namespace danos {

void SetTerminal(Terminal* terminal);

void KPrint(const char* message);

/* Prints hex values of each byte at the address */
void KPrint(const UInt8* const address, const UInt32 num_bytes);

/* Prints a single value on its own line */
void KPrint(const UInt32 value);

/* Prints a single value on its own line */
void KPrint(const UInt64 value);

}  // namespace danos
