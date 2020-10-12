#pragma once

#include "core/types.h"

namespace danos {

class BiosData {
 public:
    BiosData() = default;

    ~BiosData() = default;

    // Returns the IO port for COM1 - COM4
    // @port Should be between 1 - 4
    Uint16 GetComPort(Uint8 port) const;
};

}  // namespace danos
