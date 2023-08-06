#include <arch/x86_64/vmm/vmm.h>
#include <arch/x86_64/boot/boot.h>

void vmm_init(struct limine_memmap_response* memory_info){
    kernel_space = pmm_allocate_page();
    memset((void*)kernel_space, 0, PAGE_SIZE);

    for(uint64_t i = 0; i < memory_info->entry_count; i++){
        vmm_map(
            kernel_space, 
            (memory_range_t){
                vmm_get_virtual_address((void*)memory_info->entries[i]->base), 
                memory_info->entries[i]->length
            },
            (memory_range_t){
                (void*)memory_info->entries[i]->base, 
                memory_info->entries[i]->length 
            },
            MEMORY_FLAG_WRITABLE | MEMORY_FLAG_READABLE);
    }

    assert(!vmm_space_swap(kernel_space));

    load_info.vmm = 0;
}
