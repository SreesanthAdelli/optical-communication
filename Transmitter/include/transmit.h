#include "utilities.h"
#include "GPIO.h"
#include <stdint.h>
#include <stdbool.h>

void manchesterLineEncoding(bool transmit);

void transmitData(const uint8_t data);

void transmitByteCycle(const uint8_t byte);

void transmitPacket(const uint8_t* buffer, const uint32_t length);