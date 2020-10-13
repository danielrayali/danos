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
    
}  // namespace danos
