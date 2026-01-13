#include <stdint.h>
#include "decode.h"
#include "GPIO.h"
#include "sysinit.h"
#include "pwm.h"
#define INPUT_PIN 6
#define ADC_SAMPLE_TIME 1
#define PACKET_SIZE 4
#define START_BYTE 0xFF
#define FREQ_SCALE 20



int main(void) {
    // --- 1. Initialize system ---
    systemInit(INPUT_PIN, ADC_SAMPLE_TIME);           // GPIOs, timers, clocks, PWM, ADC

    pwmInit_pa5();                                     // Initialize PWM on PA5

    setPWMFrequency_pa5(0);                          // Start with 0 Hz

    uint32_t adc_data;
    uint64_t time_last;
    uint8_t note_idx = 0;

    while (1) {
        // Read frequency from ADC
        readAndDecodeADC(&adc_data);

        setPWMFrequency_pa5(adc_data * FREQ_SCALE);  // Set PWM frequency scaled
    }


    return 0; // Never reached
}
