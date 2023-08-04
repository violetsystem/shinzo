#include <pmm/pmm.h>
#include <vmm/vmm.h>
#include <libk/math.h>
#include <libk/assert.h>
#include <arch/x86_64/boot/limine/limine.h>

static void* pmm_get_memory_end(struct limine_memmap_response* memory_info){
    uintptr_t last_address = 0;

    for(uint64_t i = 0; i < memory_info->entry_count; i++){
        uintptr_t entry_last_address = memory_info->entries[i]->base + memory_info->entries[i]->length;
        if(entry_last_address > last_address){
            last_address = entry_last_address;
        }
    }

    return (void*)last_address;
}

static size_t pmm_get_memory_size(struct limine_memmap_response* memory_info){
    uint64_t size = 0;

    for(uint64_t i = 0; i < memory_info->entry_count; i++){
        size += memory_info->entries[i]->length;
    }

    return (size_t)size;
}

static struct limine_memmap_entry* pmm_find_free_entry(struct limine_memmap_response* memory_info, size_t minimum_size){
    for(uint64_t i = 0; i < memory_info->entry_count; i++){
        if(memory_info->entries[i]->type == LIMINE_MEMMAP_USABLE){
            if(memory_info->entries[i]->length >= minimum_size){
                return memory_info->entries[i];
            }
        }
    }   
    return NULL;
}

void pmm_init(struct limine_memmap_response* memory_info){
    void* memory_end = pmm_get_memory_end(memory_info);
    size_t memory_size = pmm_get_memory_size(memory_info);

    size_t total_page_count = DIV_ROUND_UP((size_t)memory_end, PAGE_SIZE);

    pmm_memory_info.free_page_count = 0;
    pmm_memory_info.used_page_count = 0;
    pmm_memory_info.total_page_count = (uint64_t)total_page_count;
    pmm_memory_info.reserved_page_count = (uint64_t)total_page_count;
    pmm_memory_info.total_usable_page_count = (uint64_t)total_page_count;

    size_t bitmap_size = total_page_count / 8 + 1;
    struct limine_memmap_entry* bitmap_memmap_entry = pmm_find_free_entry(memory_info, bitmap_size);

    assert(bitmap_memmap_entry);

    pmm_init_bitmap(vmm_get_virtual_address((void*)bitmap_memmap_entry->base), bitmap_size);

    /* Reserve all pages */
    memset(vmm_get_virtual_address((void*)bitmap_memmap_entry->base), 0xff, bitmap_size); 

    for(uint64_t i = 0; i < memory_info->entry_count; i++){
        if(memory_info->entries[i] != bitmap_memmap_entry){
            if(memory_info->entries[i]->type == LIMINE_MEMMAP_USABLE){
                pmm_unreserve_pages((void*)memory_info->entries[i]->base, memory_info->entries[i]->length / PAGE_SIZE);
            }
        }else{
            if(memory_info->entries[i]->length != bitmap_size){
                uintptr_t bitmap_end_rounded_to_page = memory_info->entries[i]->base + bitmap_size;
                
                if(bitmap_end_rounded_to_page % PAGE_SIZE){
                    bitmap_end_rounded_to_page -= bitmap_end_rounded_to_page % PAGE_SIZE;
                    bitmap_end_rounded_to_page += PAGE_SIZE;
                }

                pmm_unreserve_pages((void*)bitmap_end_rounded_to_page, (memory_info->entries[i]->length - bitmap_size) / PAGE_SIZE);
            }
        }
    }
}
