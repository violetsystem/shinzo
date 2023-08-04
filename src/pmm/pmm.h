#ifndef PMM_H
#define PMM_H

#include <vmm/vmm.h>
#include <arch/arch.h>
#include <lock/lock.h>
#include <types/types.h>
#include <misc/panic/panic.h>
#include <misc/bitmap/bitmap.h>


typedef struct{
    uint64_t total_page_count;
    uint64_t total_usable_page_count;
    uint64_t free_page_count;
    uint64_t reserved_page_count;
    uint64_t used_page_count;    
}memory_info_t;

extern memory_info_t pmm_memory_info;

void pmm_init_bitmap(void* address, size_t size);
void* pmm_allocate_page(void);
void* pmm_allocate_pages(uint64_t page_count);
void pmm_free_page(void* address);
void pmm_free_pages(void* address, uint64_t page_count);
void pmm_lock_page(void* address);
void pmm_lock_pages(void* address, uint64_t page_count);
void pmm_unreserve_page(void* address);
void pmm_unreserve_pages(void* address, uint64_t page_count);
void pmm_reserve_page(void* address);
void pmm_reserve_pages(void* address, uint64_t page_count);
uint64_t pmm_get_total_memory_size(void);
uint64_t pmm_get_free_memory_size(void);
uint64_t pmm_get_used_memory_size(void);
uint64_t pmm_get_reserved_memory_size(void);

#endif
