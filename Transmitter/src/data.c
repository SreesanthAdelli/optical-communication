#include "data.h"
#include <stdint.h>

uint8_t* initBuffer(uint8_t data, uint8_t* buffer, uint32_t buffer_size) {
    for (uint32_t i = 0; i < buffer_size; ++i) {
        buffer[i] = data;
    }

    return buffer;
}


uint8_t calculateCRC_8(const uint8_t* data, uint32_t length, uint8_t polynomial) {
    uint8_t crc = 0x00;   // initial value

    for (uint32_t i = 0; i < length; i++) {
        crc ^= data[i];   // XOR in next byte

        for (uint8_t bit = 0; bit < 8; bit++) {
            if (crc & 0x80) {
                crc = (crc << 1) ^ polynomial;
            } else {
                crc <<= 1;
            }
        }
    }
    return crc;
}


uint8_t* createPacket(const uint8_t startByte, const uint8_t* buffer, const uint8_t endByte, uint8_t* packet) {
    packet[0] = startByte;
    uint32_t i = 0;
    while (buffer[i] != '\0') {
        packet[i + 1] = buffer[i];
        i++;
    }
    uint8_t crcByte = calculateCRC_8(buffer, i, 0x07); // CRC-8 with polynomial 0x07
    packet[i + 1] = crcByte;
    packet[i + 2] = endByte;

    return packet;
}

