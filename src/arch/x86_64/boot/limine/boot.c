#include <pmm/pmm.h>
#include <arch/x86_64/vmm/vmm.h>
#include <arch/x86_64/boot/boot.h>
#include <arch/x86_64/boot/limine/limine.h>

/* Limine requests */

static volatile struct limine_bootloader_info_request bootloader_info_request = {
    .id = LIMINE_BOOTLOADER_INFO_REQUEST,
    .revision = 0
};

static volatile struct limine_stack_size_request stack_size_request = {
    .id = LIMINE_STACK_SIZE_REQUEST,
    .stack_size = BOOT_STACK_SIZE,
    .revision = 0
};

static volatile struct limine_hhdm_request hhdm_request = {
    .id = LIMINE_HHDM_REQUEST,
    .revision = 0
};

static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0
};

static volatile struct limine_paging_mode_request paging_mode_request = {
    .id = LIMINE_PAGING_MODE_REQUEST,
    .mode = LIMINE_PAGING_MODE_X86_64_4LVL,
    .revision = 0
};

static volatile struct limine_smp_request smp_request = {
    .id = LIMINE_SMP_REQUEST,
    .flags = LIMINE_SMP_X2APIC,
    .revision = 0
};

static volatile struct limine_memmap_request memmap_request = {
    .id = LIMINE_MEMMAP_REQUEST,
    .revision = 0
};

static volatile struct limine_rsdp_request rsdp_request = {
    .id = LIMINE_RSDP_REQUEST,
    .revision = 0
};

static volatile struct limine_smbios_request smbios_request = {
    .id = LIMINE_SMBIOS_REQUEST,
    .revision = 0
};

static volatile struct limine_boot_time_request boot_time_request = {
    .id = LIMINE_BOOT_TIME_REQUEST,
    .revision = 0
};

/* Parsing requests */
void pmm_init(struct limine_memmap_response* memory_info);

void boot_limine(void){
    hhdm_address = (void*)hhdm_request.response->offset;

    pmm_init(memmap_request.response);

    while(1){
        __asm__("hlt");
    }
}
