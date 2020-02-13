#pragma once

#include <core/types.h>

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

}  // namespace danos
