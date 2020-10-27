#include "global_descriptor_table.h"
#include "kprint.h"

namespace danos {

GlobalDescriptorTable::GlobalDescriptorTable() {
    KPrint("GDT initializing\n");
}

GlobalDescriptorTable::~GlobalDescriptorTable() {
    KPrint("GDT uninitializing\n");
}

}  // namespace danos
