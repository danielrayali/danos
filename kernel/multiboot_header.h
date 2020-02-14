#pragma once

#include "core/types.h"
#include "core/printer.h"

namespace danos {

/**
 * Offset   Type    Field Name      Note
 * 0        u32     magic           required
 * 4        u32     flags           required
 * 8        u32     checksum        required
 * 12       u32     header_addr     if flags[16] is set
 * 16       u32     load_addr       if flags[16] is set
 * 20       u32     load_end_addr   if flags[16] is set
 * 24       u32     bss_end_addr    if flags[16] is set
 * 28       u32     entry_addr      if flags[16] is set
 * 32       u32     mode_type       if flags[2] is set
 * 36       u32     width           if flags[2] is set
 * 40       u32     height          if flags[2] is set
 * 44       u32     depth           if flags[2] is set
 */
struct MultibootHeader {
    Uint32 magic;
    Uint32 flags;
    Uint32 checksum;
    Uint32 header_addr;
    Uint32 load_addr;
    Uint32 load_end_addr;
    Uint32 bss_end_addr;
    Uint32 entry_addr;
    Uint32 mode_type;
    Uint32 width;
    Uint32 height;
    Uint32 depth;
};

void PrintMultibootHeader(Printer& printer, MultibootHeader* header) {
    printer.Print("Multiboot header:");
    printer.Print("\n  magic: ");
    PrintUint32(printer, &header->magic);
    printer.Print("\n  flags: ");
    PrintUint32(printer, &header->flags);
    printer.Print("\n  checksum: ");
    PrintUint32(printer, &header->checksum);
    printer.Print("\n  header_addr: ");
    PrintUint32(printer, &header->header_addr);
    printer.Print("\n  load_addr: ");
    PrintUint32(printer, &header->load_addr);
    printer.Print("\n  load_end_addr: ");
    PrintUint32(printer, &header->load_end_addr);
    printer.Print("\n  bss_end_addr: ");
    PrintUint32(printer, &header->bss_end_addr);
    printer.Print("\n  entry_addr: ");
    PrintUint32(printer, &header->entry_addr);
    printer.Print("\n  mode_type: ");
    PrintUint32(printer, &header->mode_type);
    printer.Print("\n  width: ");
    PrintUint32(printer, &header->width);
    printer.Print("\n  height: ");
    PrintUint32(printer, &header->height);
    printer.Print("\n  depth: ");
    PrintUint32(printer, &header->depth);
    printer.Print('\n');
}

}  // namespace danos
