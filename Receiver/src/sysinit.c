#include "sysinit.h"
#include "GPIO.h"
#include "timer.h"
#include "clock.h"

void systemInit(const uint8_t INPUT_PIN, const uint8_t ADC_SAMPLE_TIME) {
    // Initialize system clock to 20 MHz
    systemClock_20MHz();

    // Initialize GPIOA
    initializeGPIOA();
    setPinAnalog(INPUT_PIN);
    initializeAnalogClock();
    full_setup_adc_channel_6(ADC_SAMPLE_TIME);

    // Start the timer
    startTimer();
}