#pragma once

#include "core/types.h"

namespace danos {

class ProgrammableInterruptController {
 public:
    ProgrammableInterruptController() = default;

    ~ProgrammableInterruptController() = default;

    void EndOfInterrupt(const Uint8 irq);

    void Remap(const Uint32 offset_master, const Uint32 offset_slave);

    void ClearMask(Uint8 irq_line);

    void SetMask(Uint8 irq_line);
};

}  // namespace danos
