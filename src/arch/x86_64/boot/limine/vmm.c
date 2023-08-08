#include <arch/x86_64/vmm/vmm.h>
#include <arch/x86_64/boot/boot.h>

extern int vmm_clear_lower_half_entries(vmm_space_t space);
extern int vmm_preload_higher_half_entries(vmm_space_t space);

void vmm_init(){
    /* limine map all we need, so all we have to do is preload the empty fields (the higher half part of the table: VMM_HALF_TABLE - VMM_END_TABLE) into the last pagination level. */
    kernel_space = vmm_get_current_space();

    vmm_clear_lower_half_entries(kernel_space);
    vmm_preload_higher_half_entries(kernel_space);

    load_info.vmm = 0;
}
