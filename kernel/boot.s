/* Declare constants for the multiboot header. */
.set MULTIBOOT_MAGIC,    0x1BADB002                             /* 'magic number' lets bootloader find the header */
.set MULTIBOOT_ALIGN,    0x1                                    /* align loaded modules on page boundaries */
.set MULTIBOOT_MEMINFO,  0x2                                    /* provide memory map */
.set multiboot_flags,    MULTIBOOT_ALIGN | MULTIBOOT_MEMINFO    /* this is the Multiboot 'flag' field */
.set multiboot_checksum, -(MULTIBOOT_MAGIC + multiboot_flags)   /* checksum of above, to prove we are multiboot */

/**
 * Declare a multiboot header that marks the program as a kernel. These are magic
 * values that are documented in the multiboot standard. The bootloader will
 * search for this signature in the first 8 KiB of the kernel file, aligned at a
 * 32-bit boundary. The signature is in its own section so the header can be
 * forced to be within the first 8 KiB of the kernel file.
 */
.section .multiboot
.align 4
.long MULTIBOOT_MAGIC
.long multiboot_flags
.long multiboot_checksum

.section .stack, "aw", @nobits
    .align 16
    stack_bottom:
    .skip 16384 # 16 KiB
    stack_top:

.section .text

.global start
.type start, @function

.extern init
.type init, @function

start:
    /**
     * To set up a stack, we set the esp register to point to the top of the
     * stack (as it grows downwards on x86 systems). This is necessarily done
     * in assembly as languages such as C cannot function without a stack.
     */
    mov $stack_top, %esp

    /**
     * This is a good place to initialize crucial processor state before the
     * high-level kernel is entered. It's best to minimize the early
     * environment where crucial features are offline. Note that the
     * processor is not fully initialized yet: Features such as floating
     * point instructions and instruction set extensions are not initialized
     * yet. The GDT should be loaded here. Paging should be enabled here.
     * C++ features such as global constructors and exceptions will require
     * runtime support to work as well.
     */

    /**
     * Enter the high-level kernel. The ABI requires the stack is 16-byte
     * aligned at the time of the call instruction (which afterwards pushes
     * the return pointer of size 4 bytes). The stack was originally 16-byte
     * aligned above and we've pushed a multiple of 16 bytes to the
     * stack since (pushed 0 bytes so far), so the alignment has thus been
     * preserved and the call is well defined.
     */
    call init
    add $4, %esp

    pushl $exit_message
    call kprint
    add $4, %esp
    cli

    /**
     * If the system has nothing more to do, put the computer into an
     * infinite loop. To do that:
     * 1) Disable interrupts with cli (clear interrupt enable in eflags).
     *    They are already disabled by the bootloader, so this is not needed.
     *    Mind that you might later enable interrupts and return from
     *    init (which is sort of nonsensical to do).
     * 2) Wait for the next interrupt to arrive with hlt (halt instruction).
     *    Since they are disabled, this will lock up the computer.
     * 3) Jump to the hlt instruction if it ever wakes up due to a
     *    non-maskable interrupt occurring or due to system management mode.
     */
    cli
1:  hlt
    jmp 1b

exit_message:
    .asciz "Kernel exited."

/**
 * Set the size of the "start" symbol to the current location '.' minus its start.
 * This is useful when debugging or when you implement call tracing.
 */
.size start, . - start
