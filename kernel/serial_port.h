#pragma once

#include "core/types.h"

namespace danos {

class SerialPort {
 public:
    SerialPort();

    ~SerialPort();

    void Transmit(const Char* string);

    // TODO(dali) Receive keyboard input
 private:
    Uint16 io_port_;
};

}  // namespace
