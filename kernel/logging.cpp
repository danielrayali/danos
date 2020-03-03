#include "kernel/logging.h"

namespace danos {

static Printer* g_printer = nullptr;

void Log(const Char letter) {
    g_printer->Print(letter);
}

void Log(const Char* message) {
    g_printer->Print(message);
}

void SetLogger(Printer* printer) {
    g_printer = printer;
}

void Log(const Uint32 value) {
    Log('0');
    Log('x');
    Uint8* value_ptr = (Uint8*)&value;
    for (Int32 i = (sizeof(Uint32) - 1); i >= 0; --i) {
        Log(ToHex(value_ptr[i] >> 4));
        Log(ToHex(value_ptr[i] & 0xF));
    }
}

void Log(const Uint64 value) {
    Log('0');
    Log('x');
    Uint8* value_ptr = (Uint8*)&value;
    for (Int32 i = (sizeof(Uint64) - 1); i >= 0; --i) {
        Log(ToHex(value_ptr[i] >> 4));
        Log(ToHex(value_ptr[i] & 0xF));
    }
}

}  // namespace danos