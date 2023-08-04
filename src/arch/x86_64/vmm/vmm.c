#include <arch/x86_64/vmm/vmm.h>

void* hhdm_address = NULL;

void* vmm_get_virtual_address(void* physical_address){
    return (void*)((uintptr_t)physical_address + (uintptr_t)hhdm_address);
}
