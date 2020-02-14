#include "vga_text_mode_buffer.h"

#include "io.h"

namespace danos {

VgaTextModeBuffer::VgaTextModeBuffer(const VgaColor background, const VgaColor foreground) {
    this->Clear();
    this->SetColors(background, foreground);
    this->UpdateCursor();
}

void VgaTextModeBuffer::UpdateCursor() const {
    const Uint16 pos = current_row_ * kVgaWidth + current_column_;
    IO::OutByte(0x3D4, 0x0F);
    IO::OutByte(0x3D5, (Uint8) (pos & 0xFF));
    IO::OutByte(0x3D4, 0x0E);
    IO::OutByte(0x3D5, (Uint8) ((pos >> 8) & 0xFF));
}

void VgaTextModeBuffer::SetColors(const VgaColor background, const VgaColor foreground) {
    for (Uint32 height = 0; height < kVgaHeight; ++height) {
        for (Uint32 width = 0; width < kVgaWidth; ++width) {
            buffer_[height * kVgaWidth + width].color = (Uint8)((Uint8)background << 4) | ((Uint8)foreground & 0x0f);
        }
    }
}

void VgaTextModeBuffer::Clear() {
    for (Uint32 height = 0; height < kVgaHeight; ++height) {
        for (Uint32 width = 0; width < kVgaWidth; ++width) {
            buffer_[height * kVgaWidth + width].value = ' ';
        }
    }
    current_column_ = 0;
    current_row_ = 0;
    this->UpdateCursor();
}

void VgaTextModeBuffer::Print(const char value) {
    if (value == '\n') {
        current_row_++;
        current_column_ = 0;
        this->UpdateCursor();
        return;
    }

    buffer_[current_row_ * kVgaWidth + current_column_].value = value;
    current_column_++;
    if (current_column_ == kVgaWidth) {
        current_column_ = 0;
        current_row_++;

        // TODO(dali) Implement scrolling
        if (current_row_ == kVgaHeight) {
            current_row_ = 0;  // Wrap around
        }
    }
    this->UpdateCursor();
}

void VgaTextModeBuffer::Print(const char* string) {
    while (*string != '\0') {
        this->Print(*string);
        string++;
    }
}

void VgaTextModeBuffer::Print(const char* string, const Uint32 length) {
    for (Uint32 i = 0; i < length; ++i) {
        this->Print(*string);
        string++;
    }
}

}  // namespace danos
