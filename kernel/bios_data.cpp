#include "bios_data.h"

namespace danos {

static const Uint32* g_bios_data_base = reinterpret_cast<Uint32*>(0x0400);

Uint16 BiosData::GetComPort(const Uint8 port) const {
    return *(g_bios_data_base + (port - 1));
}

}  // namespace danos
