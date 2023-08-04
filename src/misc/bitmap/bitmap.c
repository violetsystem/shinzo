#include <misc/bitmap/bitmap.h>

static inline uint8_t* bitmap_get_byte_address(bitmap_t* bitmap, uint64_t index){
    return (uint8_t*)(bitmap->address) + (index / 8);
}

static inline uint8_t bitmap_get_bit_offset(uint64_t index){
    return index % 8;
}

void bitmap_init(void* address, size_t size, bitmap_t* bitmap){
    bitmap->address = address;
    bitmap->size = size;
    bitmap->bit_size = size * 8;
}

bool bitmap_get_bit(bitmap_t* bitmap, uint64_t index){
    uint8_t offset = bitmap_get_bit_offset(index);
    uint8_t* byte_address = bitmap_get_byte_address(bitmap, index);
    uint8_t byte_value = *byte_address;
    return (byte_value >> offset) & 0x01;
}

void bitmap_set_bit(bitmap_t* bitmap, uint64_t index, bool value){
    uint8_t* byte_address = bitmap_get_byte_address(bitmap, index);
    uint8_t byte_position = bitmap_get_bit_offset(index);
    uint8_t byte_mask = (uint8_t)(1 << byte_position);
    
    if (value) {
        *byte_address |= byte_mask;
    } else {
        *byte_address &= ~byte_mask;
    }
}

bool bitmap_get_set_bit(bitmap_t* bitmap, uint64_t index, bool value){
    bool current_value = bitmap_get_bit(bitmap, index);
    
    if (current_value != value) {
        bitmap_set_bit(bitmap, index, value);
    }

    return current_value;
}

void bitmap_set_bits(bitmap_t* bitmap, uint64_t index, size_t count, bool value){
    for (size_t i = 0; i < count; i++){
        bitmap_set_bit(bitmap, index + i, value);
    }
}
