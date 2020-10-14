#include "vga_buffer.h"
#include "io.h"
#include "types.h"

namespace danos {

VgaBuffer::VgaBuffer(const Color foreground, const Color background) :
    buffer_(reinterpret_cast<UInt16*>(0xB8000)),
    x_(0),
    y_(0),
    foreground_(foreground),
    background_(background) {
    this->FindStartPosition();
    for (UInt32 i = 0; i < kWidth; ++i) {
        erased_line_[i] = ' ';
    }
}

UInt16 VgaBuffer::GetColor() const {
    return static_cast<UInt16>(foreground_) | (static_cast<UInt16>(background_) << 4);
}

bool VgaBuffer::Put(const char data) {
    if (data == '\n') {
        this->AdvanceLine();
        return true;
    }

    const UInt16 color = GetColor();
    buffer_[y_ * kWidth + x_] = data | (color << 8);

    x_++;
    if (x_ == kWidth) {
        this->AdvanceLine();
        return true;
    }

    this->UpdateCursor();
    return false;
}

void VgaBuffer::AdvanceLine() {
    y_++;
    if (y_ == kHeight) {
        // Save the first line as the last line erased
        for (UInt32 i = 0; i < kWidth; ++i) {
            erased_line_[i] = buffer_[i];
        }
        // Copy all lines up one line
        for (UInt32 i = 0; i < kHeight - 1; ++i) {
            for (UInt32 j = 0; j < kWidth; ++j) {
                buffer_[i * kWidth + j] = buffer_[(i+1) * kWidth + j];
            }
        }
        for (UInt32 i = 0; i < kWidth; ++i) {
            buffer_[(kHeight - 1) * kWidth + i] = ' ';
        }
        y_--;
    }
    x_ = 0;
    this->UpdateCursor();
}

void VgaBuffer::FindStartPosition() {
    for (UInt32 y = 0; y < kHeight; ++y) {
        for (UInt32 x = 0; x < kWidth; ++x) {
            if ((buffer_[y*kWidth + x] & 0x00ff) != ' ') {
                x_ = x;
                y_ = y;
            }
        }
    }

    if ((y_ != 0) && (x_ != 0)) {
        this->AdvanceLine();
    }

    this->UpdateCursor();
}

void VgaBuffer::UpdateCursor() {
    UInt16 pos = y_ * kWidth + x_;

    // Set cursor color
    const UInt16 color = GetColor();
    buffer_[y_ * kWidth + x_] = (buffer_[y_ * kWidth + x_] & 0x00ff) | (color << 8);

    // Update cursor using VGA IO ports
    IO::Out(static_cast<UInt16>(0x3D4), 0x0F);
    IO::Out(static_cast<UInt16>(0x3D5), static_cast<UInt8>(pos & 0xFF));
    IO::Out(static_cast<UInt16>(0x3D4), 0x0E);
    IO::Out(static_cast<UInt16>(0x3D5), static_cast<UInt8>((pos >> 8) & 0xFF));
}

}  // namespace danos
