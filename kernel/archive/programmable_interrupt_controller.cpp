#include "programmable_interrupt_controller.h"

#include "kernel/io.h"

namespace danos {

static const Uint8 PIC1            = 0x20;        /* IO base address for master PIC */
static const Uint8 PIC2            = 0xA0;        /* IO base address for slave PIC */
static const Uint8 PIC1_COMMAND    = PIC1;
static const Uint8 PIC1_DATA       = (PIC1+1);
static const Uint8 PIC2_COMMAND    = PIC2;
static const Uint8 PIC2_DATA       = (PIC2+1);

static const Uint8 ICW1_ICW4         = 0x01;    /* ICW4 (not) needed */
static const Uint8 ICW1_SINGLE       = 0x02;    /* Single (cascade) mode */
static const Uint8 ICW1_INTERVAL4    = 0x04;    /* Call address interval 4 (8) */
static const Uint8 ICW1_LEVEL        = 0x08;    /* Level triggered (edge) mode */
static const Uint8 ICW1_INIT         = 0x10;    /* Initialization - required! */

static const Uint8 ICW4_8086         = 0x01;    /* 8086/88 (MCS-80/85) mode */
static const Uint8 ICW4_AUTO         = 0x02;    /* Auto (normal) EOI */
static const Uint8 ICW4_BUF_SLAVE    = 0x08;    /* Buffered mode/slave */
static const Uint8 ICW4_BUF_MASTER   = 0x0C;    /* Buffered mode/master */
static const Uint8 ICW4_SFNM         = 0x10;    /* Special fully nested (not) */
static const Uint8 PIC_EOI           = 0x20;    /* End-of-interrupt command code */

void ProgrammableInterruptController::EndOfInterrupt(const Uint8 irq) {
    if(irq >= 8)
        IO::Out(PIC2_COMMAND, PIC_EOI);
    IO::Out(PIC1_COMMAND, PIC_EOI);
}

void ProgrammableInterruptController::Remap(const Uint32 offset_master, const Uint32 offset_slave) {
    Uint8 master_mask = IO::In(PIC1_DATA);
    Uint8 slave_mask = IO::In(PIC2_DATA);

    master_mask = IO::In(PIC1_DATA);                        // save masks
    slave_mask = IO::In(PIC2_DATA);

    IO::Out(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);  // starts the initialization sequence (in cascade mode)
    IO::Wait();
    IO::Out(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
    IO::Wait();
    IO::Out(PIC1_DATA, offset_master);                 // ICW2: Master PIC vector offset
    IO::Wait();
    IO::Out(PIC2_DATA, offset_slave);                 // ICW2: Slave PIC vector offset
    IO::Wait();
    IO::Out(PIC1_DATA, 4);                       // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
    IO::Wait();
    IO::Out(PIC2_DATA, 2);                       // ICW3: tell Slave PIC its cascade identity (0000 0010)
    IO::Wait();

    IO::Out(PIC1_DATA, ICW4_8086);
    IO::Wait();
    IO::Out(PIC2_DATA, ICW4_8086);
    IO::Wait();

    IO::Out(PIC1_DATA, master_mask);   // restore saved masks.
    IO::Out(PIC2_DATA, slave_mask);
}

// TODO(dali) Disable the PIC if you're going to use the APIC
// mov al, 0xff
// out 0xa1, al
// out 0x21, al

void ProgrammableInterruptController::SetMask(Uint8 irq_line) {
    Uint16 port;
    Uint8 value;

    if (irq_line < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        irq_line -= 8;
    }
    value = IO::In(port) | (1 << irq_line);
    IO::Out(port, value);
}

void ProgrammableInterruptController::ClearMask(Uint8 irq_line) {
    Uint16 port;
    Uint8 value;

    if (irq_line < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        irq_line -= 8;
    }
    value = IO::In(port) & ~(1 << irq_line);
    IO::Out(port, value);
}

}  // namespace danos
