#include <memory/memory.h>

void memset(void* start, uint8_t value, size_t size){
    for (uint64_t i = 0; i < size; i += sizeof(uint8_t)){
        *(uint8_t*)((uint64_t)start + i) = value;
    }
}
