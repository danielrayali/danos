#pragma once

#include <core/types.h>

namespace danos {

inline Uint64 StringLength(const Char* string) {
    Uint64 length = 0;
    while (string[length] != '\0') { length++; }
    return length;
}

inline Char ToHex(Uint32 value) {
    if (value < 10) {
        return ('0' + value);
    } else {
        return ('a' + (value - 10));
    }
}

class Printer {
 public:
    virtual void Print(const Char value) = 0;

    // Will attempt to find the length of the string
    virtual void Print(const Char* string) = 0;

    virtual void Print(const Char* string, const Uint32 length) = 0;
};

inline void PrintUint32(Printer& printer, Uint32* value) {
    printer.Print('0');
    printer.Print('x');
    Uint8* value_ptr = (Uint8*)value;
    for (Int32 i = 3; i >= 0; --i) {
        printer.Print(ToHex(value_ptr[i] >> 4));
        printer.Print(ToHex(value_ptr[i] & 0xF));
    }
}

}  // namespace danos