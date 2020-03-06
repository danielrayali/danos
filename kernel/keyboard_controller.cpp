#include "kernel/keyboard_controller.h"
#include "kernel/io.h"
#include "core/types.h"

namespace danos {

static Uint8 kDataPort = 0x60;
static Uint8 kStatusRegister = 0x64;
static Uint8 kCommandRegister = 0x64;

void WaitForEmptyBuffer() {
    while ((IO::In(kStatusRegister) & 0x01) == 1) {
        IO::Out(kCommandRegister, 0xD0);
        IO::In(kDataPort);  // Throw away
    }
}

void KeyboardController::InitializeA20() {
    IO::Out(kCommandRegister, 0xAD);
    WaitForEmptyBuffer();


}

}  // namespace danos
