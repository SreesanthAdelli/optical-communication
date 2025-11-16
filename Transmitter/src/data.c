#include "data.h"
#include <stdint.h>

uint8_t* initBuffer(uint8_t data, uint8_t* buffer, uint32_t buffer_size) {
    for (uint32_t i = 0; i < buffer_size; ++i) {
        buffer[i] = data;
    }

    return buffer;
}