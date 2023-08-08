#ifndef MEMORY_H
#define MEMORY_H

#include <types/types.h>

typedef struct{
    void* address;
    size_t size;
}memory_range_t;

typedef uint8_t memory_flags_t;

#define MEMORY_FLAG_READABLE            (1 << 0)
#define MEMORY_FLAG_WRITABLE            (1 << 1)
#define MEMORY_FLAG_EXECUTABLE          (1 << 2)
#define MEMORY_FLAG_USER                (1 << 3)
#define MEMORY_FLAG_DMA                 (1 << 4)

void memset(void* start, uint8_t value, size_t size);
void memcpy(void* dst, void* src, size_t size);

#endif
