#ifndef MISC_ARCH_X86_64_VMM_H
#define MISC_ARCH_X86_64_VMM_H

#include <types/types.h>

extern void* hhdm_address;

static inline void* vmm_get_virtual_address(void* physical_address){
    return (void*)((uintptr_t)physical_address + (uintptr_t)hhdm_address);
}

#endif
