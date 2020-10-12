#pragma once

#include "types.h"

namespace danos {

enum VgaColor : UInt16 {
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

class VgaBuffer {
 public:
    VgaBuffer(UInt16* address = reinterpret_cast<UInt16*>(0xB8000), const UInt32 size = 80*25);

    ~VgaBuffer() = default;

    void Clear();

    void SetForegroundColor(const VgaColor foreground);

    void SetBackgroundColor(const VgaColor background);

    void SetByte(const UInt32 position, const char data);

 private:
    UInt16* address_;
    const UInt32 size_;
    VgaColor background_;
    VgaColor foreground_;
};

}  // namespace danos
