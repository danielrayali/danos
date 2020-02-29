#include "kernel/serial_port.h"
#include "kernel/bios_data.h"
#include "kernel/io.h"

namespace danos {

SerialPort::SerialPort() {
    BiosData bios_data;
    io_port_ = bios_data.GetComPort(1);
}

Char SerialPort::Read() {
    return IO::InByte(io_port_);
}

void SerialPort::Print(const Char* string) {
    while (*string != '\0') {
        this->Print(*string);
        string++;
    }
}

void SerialPort::Print(const Char letter) {
    IO::OutByte(io_port_, letter);
}

}  // namespace danos
