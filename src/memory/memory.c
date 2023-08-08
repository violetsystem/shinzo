#include <memory/memory.h>

void memset(void* start, uint8_t value, size_t size){
    for(uintptr_t i = 0; i < size; i += sizeof(uint8_t)){
        *(uint8_t*)((uintptr_t)start + i) = value;
    }
}

void memcpy(void* dst, void* src, size_t size){
    for(uintptr_t i = 0; i < size; i += sizeof(uint8_t)){
        *(uint8_t*)((uintptr_t)dst + i) = *(uint8_t*)((uintptr_t)src + i);
    }
}
