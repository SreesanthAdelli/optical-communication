#include "transmit.h"
#include "GPIO.h"
#include "utilities.h"
#include "timer.h"
#include <stdint.h>
#include <stdbool.h>

#define LASER_PIN               6
#define LED_PIN                 5
#define BIT_PERIOD_US           100  // 100 microseconds = 10 kbps

void transmitPacket(const uint8_t* buffer, const uint32_t length) {
    uint32_t next_transition_time = getTicks();
    
    setPin(LED_PIN, true);
    
    // Transmit packet 100 times continuously
    for (uint32_t repeat = 0; repeat < 100; repeat++) {
        for (uint32_t byte_idx = 0; byte_idx < length; byte_idx++) {
            uint8_t data = buffer[byte_idx];
            
            // Transmit each bit MSB first
            for (int bit_idx = 7; bit_idx >= 0; bit_idx--) {
                bool bit = (data >> bit_idx) & 1;
                
                // Manchester encoding: bit=1 is 0→1, bit=0 is 1→0
                if (bit) {
                    // First half: low
                    setPin(LASER_PIN, false);
                    next_transition_time += (BIT_PERIOD_US / 2);
                    while (getTicks() < next_transition_time);
                    
                    // Second half: high
                    setPin(LASER_PIN, true);
                    next_transition_time += (BIT_PERIOD_US / 2);
                    while (getTicks() < next_transition_time);
                } else {
                    // First half: high
                    setPin(LASER_PIN, true);
                    next_transition_time += (BIT_PERIOD_US / 2);
                    while (getTicks() < next_transition_time);
                    
                    // Second half: low
                    setPin(LASER_PIN, false);
                    next_transition_time += (BIT_PERIOD_US / 2);
                    while (getTicks() < next_transition_time);
                }
            }
        }
    }
    
    setPin(LASER_PIN, false);
    setPin(LED_PIN, false);
}