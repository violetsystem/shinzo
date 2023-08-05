#ifndef VMM_H
#define VMM_H

#include <arch/arch.h>
#include <types/types.h>
#include <memory/memory.h>

vmm_space_t vmm_create_space(void);

vmm_space_t vmm_get_kernel_space(void);

vmm_space_t vmm_get_current_space(void);

int vmm_destroy_space(vmm_space_t space);

int vmm_space_swap(vmm_space_t space);

int vmm_map(vmm_space_t space, memory_range_t virtual_range, memory_range_t physical_range, memory_flags_t flags);

int vmm_update_flags(vmm_space_t space, memory_range_t virtual_range, memory_flags_t flags);

int vmm_unmap(vmm_space_t space, memory_range_t virtual_range);

void* vmm_get_physical_address(vmm_space_t space, void* virtual_address);

static inline void* vmm_get_virtual_address(void* physical_address){
    return (void*)((uintptr_t)physical_address + (uintptr_t)hhdm_address);
}

#endif
