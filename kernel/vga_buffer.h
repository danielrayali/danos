#pragma once

#include "types.h"

namespace danos {

class VgaBuffer {
 public:
    enum Color : UInt16 {
        BLACK = 0,
        BLUE = 1,
        GREEN = 2,
        CYAN = 3,
        RED = 4,
        MAGENTA = 5,
        BROWN = 6,
        LIGHT_GREY = 7,
        DARK_GREY = 8,
        LIGHT_BLUE = 9,
        LIGHT_GREEN = 10,
        LIGHT_CYAN = 11,
        LIGHT_RED = 12,
        LIGHT_MAGENTA = 13,
        LIGHT_BROWN = 14,
        WHITE = 15
    };

    const UInt32 kWidth = 80;

    const UInt32 kHeight = 25;

    VgaBuffer(const Color foreground, const Color background);

    ~VgaBuffer() = default;

    void Put(const char data);

 private:
    void FindCurrentPosition();

    void AdvanceLine();

    UInt16* buffer_;
    const UInt32 size_;
    UInt32 x_;
    UInt32 y_;
    Color foreground_;
    Color background_;
};

}  // namespace danos
