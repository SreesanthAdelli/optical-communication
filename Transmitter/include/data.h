#pragma once


#include <stdint.h>

uint8_t* initBuffer(uint8_t data, uint8_t* buffer, uint32_t buffer_size);


uint8_t* createPacket(const uint8_t startByte, const uint8_t* buffer, const uint8_t endByte, uint8_t* packet);
