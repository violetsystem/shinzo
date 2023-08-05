#include <arch/x86_64/vmm/vmm.h>

#define VMM_START_TABLE     0x0
#define VMM_HALF_TABLE      0x100
#define VMM_END_TABLE       0x200

void* hhdm_address = NULL;
vmm_space_t kernel_space = NULL;

struct vmm_page_table{ 
    uint64_t entries[512];
}__attribute__((packed));

vmm_space_t vmm_create_space(void){
    return NULL;
}

vmm_space_t vmm_get_kernel_space(void){
    return kernel_space;
}

vmm_space_t vmm_get_current_space(void){
    return asm_get_paging_entry();
}

int vmm_destroy_space(vmm_space_t space){
    if(space == kernel_space){
        return EACCES;
    }

    return 0;
}

int vmm_space_swap(vmm_space_t space){
    asm_set_paging_entry(space);
    return 0;
}

int vmm_map(vmm_space_t space, memory_range_t virtual_range, memory_range_t physical_range, memory_flags_t flags){
    return 0;
}

int vmm_update_flags(vmm_space_t space, memory_range_t virtual_range, memory_flags_t flags){
    return 0;    
}

int vmm_unmap(vmm_space_t space, memory_range_t virtual_range){
    return 0;
}

void* vmm_get_physical_address(vmm_space_t space, void* virtual_address){
    return NULL;
}
