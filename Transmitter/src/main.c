#include "GPIO.h"
#include "utilities.h"
#include "data.h"
#include "transmit.h"
#include <stdint.h>
#include <stdbool.h>
#define LASER_PIN               6
#define LED_PIN                 5
#define BUFFER_SIZE             1000


int main(void) {

    // Enable GPIOA clock
    initializeGPIOA();

    // Configure PA6 as output (Laser control)
    setPinDigitalOutput(LASER_PIN);
    setPinDigitalOutput(LED_PIN);

    // Data initialization
    const uint8_t data = 0b00101010;   // Data Byte for testing - number 42
    uint8_t buffer[BUFFER_SIZE];
    initBuffer(data, buffer, BUFFER_SIZE);

    while(1) {
        transmitBuffer(buffer, BUFFER_SIZE);
    }

    return 0; // Never reached
}
