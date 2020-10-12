#include "vga_buffer.h"

namespace danos {

VgaBuffer::VgaBuffer(UInt16* address, const UInt32 size) : 
    address_(address), 
    size_(size), 
    background_(VgaColor::BLACK), 
    foreground_(VgaColor::WHITE) { }

void VgaBuffer::Clear() {
    for (UInt32 i = 0; i < size_; ++i) {
        address_[i] = ' ';
    }
}

void VgaBuffer::SetForegroundColor(const VgaColor foreground) {
    foreground_ = foreground;
}

void VgaBuffer::SetBackgroundColor(const VgaColor background) {
    background_ = background;
}

void VgaBuffer::SetByte(const UInt32 position, const char data) {
    const UInt16 color = foreground_ | (background_ << 4);
    address_[position] = data | (color << 8);
}

}  // namespace danos
