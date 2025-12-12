#include "transmit.h"
#include "GPIO.h"
#include "utilities.h"
#include <stdint.h>
#include <stdbool.h>
#define LASER_PIN               6
#define LED_PIN                 5
#define SYSTEM_CLOCK_HZ         2000000  // 2 MHz
#define ONE_SECOND              SYSTEM_CLOCK_HZ  // 1 second at 2 MHz clock
#define BUFFER_SIZE             1000

// 2 MHz clock
const uint8_t bandwidth = 10; // in Hz
const uint32_t bitPeriod = SYSTEM_CLOCK_HZ / bandwidth; // in clock cycles



void manchesterLineEncoding(bool transmit) {
    if (transmit) {
        setPin(LASER_PIN, true);
        delay(bitPeriod / 2);
        setPin(LASER_PIN, false);
        delay(bitPeriod / 2);
    } else {
        setPin(LASER_PIN, false);
        delay(bitPeriod / 2);
        setPin(LASER_PIN, true);
        delay(bitPeriod / 2);
    }
}


void transmitData(const uint8_t data) {
    for (int i = 0; i < 8; ++i) {
        bool transmit = (data >> i) & 1;
        manchesterLineEncoding(transmit);
    }
}

void transmitByteCycle(const uint8_t byte) {
    // Signal start of byte transmission
    setPin(LED_PIN, true);

    // Transmit data
    transmitData(byte);
    setPin(LASER_PIN, false); // Ensure laser is off after transmission

    // Turn off LED after transmission
    setPin(LED_PIN, false);
    delay(.05 * ONE_SECOND); // 2 second delay between byte transmissions
}


void transmitPacket(const uint8_t* buffer, const uint32_t length) {
    for (uint32_t i = 0; i < length; ++i) {
        transmitByteCycle(buffer[i]);
    }
}