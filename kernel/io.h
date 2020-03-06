#pragma once

#include "core/types.h"

namespace danos {

class IO {
 public:
    static inline void Out(const Uint16 port, const Uint8 value) {
        /**
         * There's an outb %al, $imm8  encoding, for compile-time constant port numbers that fit in 8b.  (N constraint).
         * Wider immediate constants would be truncated at assemble-time (e.g. "i" constraint).
         * The  outb  %al, %dx  encoding is the only option for all other cases.
         * %1 expands to %dx because  port  is a uint16_t.  %w1 could be used if we had the port number a wider C type
         */
        asm volatile ( "outb %0, %1" : : "a"(value), "Nd"(port) );
    }

    static inline Uint8 In(const Uint16 port) {
        Uint8 ret;
        asm volatile ( "inb %1, %0"
                    : "=a"(ret)
                    : "Nd"(port) );
        return ret;
    }

    static inline void Wait(void) {
        /* Port 0x80 is used for 'checkpoints' during POST. */
        /* The Linux kernel seems to think it is free for use :-/ */
        asm volatile ( "outb %%al, $0x80" : : "a"(0) );
        /* %%al instead of %0 makes no difference.  TODO: does the register need to be zeroed? */
    }
};

}