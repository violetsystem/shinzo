#include <arch/x86_64/vmm/vmm.h>
#include <arch/x86_64/boot/boot.h>

void vmm_init(struct limine_memmap_response* memory_info){
    kernel_space = pmm_allocate_page();
    memset((void*)kernel_space, 0, PAGE_SIZE);

    // assert(!vmm_space_swap(kernel_space));

    load_info.vmm = 0;
}
