#pragma once

#include "core/types.h"
#include "core/printer.h"

namespace danos {

class SerialPort : public Printer{
public:
    SerialPort();

    ~SerialPort() = default;

    Char Read();

    void Print(const Char* string) override;

    void Print(const Char letter) override;

    // TODO(dali) Receive keyboard input

private:
    Uint16 io_port_;
};

}  // namespace
