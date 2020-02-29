#pragma once

#include "core/printer.h"

namespace danos {

class InterruptVectorTable {
 public:
    InterruptVectorTable() = default;

    ~InterruptVectorTable() = default;

    void Initialize(Printer& printer);
};

}  // namespace danos
