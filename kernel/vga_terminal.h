#pragma once

#include "terminal.h"
#include "vga_buffer.h"

namespace danos {

/**
 * Terminal adapter for VgaBuffer
 */
class VgaTerminal : public Terminal {
 public:
    VgaTerminal();

    virtual ~VgaTerminal() = default;

    void Print(const char* message) override;

 private:
    VgaBuffer vga_buffer_;
};

}  // namespace danos
