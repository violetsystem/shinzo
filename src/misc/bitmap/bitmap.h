#ifndef MISC_BITMAP_H
#define MISC_BITMAP_H

#include <types/types.h>
#include <memory/memory.h>

typedef struct{
    void* address;
    size_t size;
    uint64_t bit_size;
}bitmap_t;

void bitmap_init(void* address, size_t size, bitmap_t* bitmap);

bool bitmap_get_bit(bitmap_t* bitmap, uint64_t index);
void bitmap_set_bit(bitmap_t* bitmap, uint64_t index, bool value);
bool bitmap_get_set_bit(bitmap_t* bitmap, uint64_t index, bool value);

void bitmap_set_bits(bitmap_t* bitmap, uint64_t index, size_t count, bool value);

#endif
