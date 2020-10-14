#include "vga_buffer.h"

namespace danos {

VgaBuffer::VgaBuffer(const Color foreground, const Color background) :
    buffer_(reinterpret_cast<UInt16*>(0xB8000)),
    size_(kWidth*kHeight),
    x_(0),
    y_(0),
    foreground_(foreground),
    background_(background) { 
    this->FindCurrentPosition();
    for (UInt32 i = 0; i < kWidth; ++i) {
        erased_line_[i] = ' ';
    }
}

bool VgaBuffer::Put(const char data) {
    if (data == '\n') {
        this->AdvanceLine();
        return true;
    }

    const UInt16 color = static_cast<UInt16>(foreground_) | (static_cast<UInt16>(background_) << 4);
    buffer_[y_ * kWidth + x_] = data | (color << 8);

    x_++;
    if (x_ == kWidth) {
        this->AdvanceLine();
        return true;
    }
    
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
}

void VgaBuffer::FindCurrentPosition() {
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
}

}  // namespace danos
