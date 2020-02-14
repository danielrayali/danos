#pragma once

#include "core/types.h"
#include "core/printer.h"

namespace danos {

enum class VgaColor : Uint8 {
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

struct VgaTextModeData {
    Uint8 value;
    Uint8 color;
};

class VgaTextModeBuffer : public Printer {
 public:
    VgaTextModeBuffer(const VgaColor background, const VgaColor foreground);

    ~VgaTextModeBuffer() = default;

    void SetColors(const VgaColor background, const VgaColor foreground);

    void Print(const Char value) override;

    void Print(const Char* string) override;

    void Print(const Char* string, const Uint32 length) override;

    void Clear();

 private:
    static const Uint32 kVgaWidth = 80;

    static const Uint32 kVgaHeight = 25;

    VgaTextModeData* buffer_ = reinterpret_cast<VgaTextModeData*>(0xB8000);

    Uint32 current_row_ = 0;

    Uint32 current_column_ = 0;

    // Updates cursor to the current row and columns position
    void UpdateCursor() const;

    void IncreaseRow();
};

}  // namespace danos
