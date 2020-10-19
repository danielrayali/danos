#include "kprint.h"
#include "terminal.h"
#include "vga_buffer.h"

namespace danos {

Terminal* g_terminal = nullptr;

void SetTerminal(Terminal* terminal) {
    g_terminal = terminal;
}

void KPrint(const char* message) {
    g_terminal->Print(message);
}

void KPrint(const UInt32 value) {
    char value_str[12] = "0000000000\n";
    value_str[11] = '\0';
    UInt64 divider = 1;
    for (int i = 0; i < 10; ++i) {
        value_str[9 - i] = '0' + ((value/divider) % 10);
        divider *= 10;
    }
    g_terminal->Print(value_str);
}

void KPrint(const UInt64 value) {
    char value_str[21] = "0000000000000000000\n";
    value_str[20] = '\0';
    UInt64 divider = 1;
    for (int i = 0; i < 19; ++i) {
        value_str[18 - i] = '0' + ((value/divider) % 10);
        divider *= 10;
    }
    g_terminal->Print(value_str);
}

}  // namespace danos
