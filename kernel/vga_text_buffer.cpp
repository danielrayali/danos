#include "vga_text_buffer.h"
#include "kernel/io.h"
#include "core/types.h"

namespace danos {

VgaTextBuffer::VgaTextBuffer(const VgaColor background, const VgaColor foreground) {
    this->Clear();
    this->SetColors(background, foreground);
    this->UpdateCursor();
}

void VgaTextBuffer::UpdateCursor() const {
    const Uint16 pos = current_row_ * kVgaWidth + current_column_;
    IO::OutByte(0x3D4, 0x0F);
    IO::OutByte(0x3D5, (Uint8) (pos & 0xFF));
    IO::OutByte(0x3D4, 0x0E);
    IO::OutByte(0x3D5, (Uint8) ((pos >> 8) & 0xFF));
}

void VgaTextBuffer::SetColors(const VgaColor background, const VgaColor foreground) {
    for (Uint32 height = 0; height < kVgaHeight; ++height) {
        for (Uint32 width = 0; width < kVgaWidth; ++width) {
            buffer_[height * kVgaWidth + width].color = (Uint8)((Uint8)background << 4) | ((Uint8)foreground & 0x0f);
        }
    }
}

void VgaTextBuffer::Clear() {
    for (Uint32 height = 0; height < kVgaHeight; ++height) {
        for (Uint32 width = 0; width < kVgaWidth; ++width) {
            buffer_[height * kVgaWidth + width].value = ' ';
        }
    }
    current_column_ = 0;
    current_row_ = 0;
    this->UpdateCursor();
}

void VgaTextBuffer::IncreaseRow() {
    if ((current_row_ + 1) == kVgaHeight) {
        for (Uint32 i = 0; i < (kVgaHeight - 1); ++i) {
            for (Uint32 j = 0; j < kVgaWidth; ++j) {
                buffer_[i * kVgaWidth + j] = buffer_[(i + 1) * kVgaWidth + j];
            }
        }
        for (Uint32 i = 0; i < kVgaWidth; ++i) {
            buffer_[(kVgaHeight - 1) * kVgaWidth + i].value = ' ';
        }
    } else {
        current_row_++;
    }

    current_column_ = 0;
}

void VgaTextBuffer::Print(const Char value) {
    if (value == '\n') {
        this->IncreaseRow();
        this->UpdateCursor();
        return;
    }

    buffer_[current_row_ * kVgaWidth + current_column_].value = value;
    current_column_++;
    if (current_column_ == kVgaWidth) {
        this->IncreaseRow();
    }

    this->UpdateCursor();
}

void VgaTextBuffer::Print(const Char* string) {
    while (*string != '\0') {
        this->Print(*string);
        string++;
    }
}

}  // namespace danos
