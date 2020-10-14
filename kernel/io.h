#pragma once

#include "types.h"

namespace danos {

class IO {
 public:
    static void Out(UInt16 port, UInt8 value);
};

}  // namespace danos
