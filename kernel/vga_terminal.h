#pragma once

#include "types.h"
#include "vga_buffer.h"

namespace danos {

class VgaTerminal {
 public:
 	static VgaTerminal& Default();	

 	VgaTerminal();

 	~VgaTerminal() = default;

 	void Print(const char letter);

 	void Print(const char* string, const UInt64 size);

 	void Print(const char* string);

 private:
 	VgaBuffer vga_buffer_;
    UInt64 position_ = 0;
};
	
}  // namespace danos
