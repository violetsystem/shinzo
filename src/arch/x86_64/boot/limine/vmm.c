#include <arch/x86_64/vmm/vmm.h>
#include <arch/x86_64/boot/boot.h>

extern int vmm_preload_higher_half_entries(vmm_space_t space);

void vmm_init(struct limine_memmap_response* memory_info){
    /* limine map everything we need so we just need to preload empty fields (higher half : VMM_HALF_TABLE - VMM_END_TABLE) in the last level of paging */
    kernel_space = vmm_get_current_space();

    vmm_preload_higher_half_entries(kernel_space);

    load_info.vmm = 0;
}
