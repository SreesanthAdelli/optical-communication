#include <stdint.h>
#include "stm32f446xx.h"
#include "decode.h"
#include "timer.h"
#include "GPIO.h"

#define BIT_PERIOD_US 100
#define ADC_THRESHOLD 100  // Threshold to determine high/low level from ADC reading
#define TOLERANCE 10     


void readAndDecodeADC(uint8_t* frequency) {
    while (1) {

        int last_level = -1;
        uint64_t last_edge_time = 0;
        uint64_t next_sample_time = 0;
    


        // Clock recovery phase
        while (1) {
            uint64_t now = getTicks();
            uint16_t voltage = readADCData();
            uint8_t level = (voltage > ADC_THRESHOLD) ? 1 : 0;
            
            if (last_level == -1) {
                last_level = level;
                last_edge_time = now;
                continue;
            }
            
            // Detect edge for clock recovery
            if (level != last_level) {
                uint64_t period = now - last_edge_time;
                
                // Look for edge at ~1 bit period for clock recovery
                if (period >= BIT_PERIOD_US * (1 - 10) && 
                    period <= BIT_PERIOD_US * (1 + 10)) {
                    // Clock recovered - set up for sampling
                    next_sample_time = now + BIT_PERIOD_US + 5; // Slightly after next bit period
                    break; // Exit clock recovery
                }
                
                last_level = level;
                last_edge_time = now;
            }
        }

        // Data sampling phase

        uint8_t start_byte = 0;

        while(start_byte != 0xFF) {
            // Sample bits to form start byte
            while (getTicks() < next_sample_time);
            
            uint16_t voltage = readADCData();
            uint8_t bit = (voltage > ADC_THRESHOLD) ? 1 : 0;

            start_byte = (start_byte << 1) | bit;
            
            next_sample_time += BIT_PERIOD_US;
        }

        uint8_t frequency_byte = 0;
        uint8_t checksum_byte = 0;


        for (int i = 0; i < 8; i++) {
            // Wait until next sample time
            while (getTicks() < next_sample_time);
            
            uint16_t voltage = readADCData();
            uint8_t bit = (voltage > ADC_THRESHOLD) ? 1 : 0;

            frequency_byte = (frequency_byte << 1) | bit;
            
            next_sample_time += BIT_PERIOD_US;
        }

        for (int i = 0; i < 8; i++) {
            // Wait until next sample time
            while (getTicks() < next_sample_time);
            
            uint16_t voltage = readADCData();
            uint8_t bit = (voltage > ADC_THRESHOLD) ? 1 : 0;

            checksum_byte = (checksum_byte << 1) | bit;
            
            next_sample_time += BIT_PERIOD_US;
        }

        // Verify checksum
        if ((frequency_byte + checksum_byte) % 256 == 0) {
            *frequency = frequency_byte;
            return; // Valid packet found
        } else {
            // Invalid packet, continue to next iteration
            continue;
        }
    }
}
