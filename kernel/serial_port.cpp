#include "kernel/serial_port.h"
#include "kernel/bios_data.h"
#include "kernel/io.h"

namespace danos {

SerialPort::SerialPort() {
    BiosData bios_data;
    io_port_ = bios_data.GetComPort(1);
}

SerialPort::~SerialPort() {}

void SerialPort::Transmit(const Char* string) {
    while (*string != '\0') {
        IO::OutByte(io_port_, *string);
        string++;
    }
}

}  // namespace danos