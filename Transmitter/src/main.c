#include "GPIO.h"
#include "utilities.h"
#include <stdint.h>
#include <stdbool.h>
#define LASER_PIN               6
#define LED_PIN                 5
#define SYSTEM_CLOCK_HZ         2000000  // 2 MHz
#define ONE_SECOND        SYSTEM_CLOCK_HZ  // 1 second at 2 MHz clock
#define BUFFER_SIZE             1000

// 2 MHz clock
const int bandwidth = 1; // in Hz
const int bitPeriod = SYSTEM_CLOCK_HZ / bandwidth; // in clock cycles
const uint8_t data = 0b00101010;   // Data Byte for testing - number 42
uint8_t buffer[BUFFER_SIZE];

void initBuffer() {
    for (int i = 0; i < BUFFER_SIZE; ++i) {
        buffer[i] = data;
    }
}


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

void flashPin_10(uint8_t pin) {
    togglePin(pin);
    delay(0.1 * ONE_SECOND);
}


int main(void) {

    // Enable GPIOA clock
    initializeGPIOA();

    // Configure PA6 as output (Laser control)
    setPinOutput(LASER_PIN);
    setPinOutput(LED_PIN);

    initBuffer();

    while(1) {
        for (int i = 0; i < BUFFER_SIZE; ++i) {
            transmitByteCycle(buffer[i]);
        }
    }

    return 0; // Never reached
}
