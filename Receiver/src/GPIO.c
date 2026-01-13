// GPIO pin control implementation

#include "GPIO.h"
#include "stm32f446xx.h"
#include <stdint.h>
#include <stdbool.h>



void initializeGPIOA() {
    // Enable GPIOA clock
    RCC_AHB1ENR |= (1 << 0); // GPIOAEN
}

void setPinDigitalOutput(uint8_t pin) {
    // Set specified pin as output (MODERx = 01)
    GPIOA_MODER &= ~(0x3 << (pin * 2)); // Clear mode bits
    GPIOA_MODER |=  (0x1 << (pin * 2)); // Set as output
}

void setPinAnalog(uint8_t pin) {
    // Set specified pin as analog (MODERx = 11)
    GPIOA_MODER |=  (0x3 << (pin * 2)); // Set as analog
}

void setPin(uint8_t pin, bool value) {
    if(value) {
        GPIOA_ODR |= (1 << pin); // Set pin
    } else {
        GPIOA_ODR &= ~(1 << pin); // Clear pin
    }
}

void togglePin(uint8_t pin) {
    GPIOA_ODR ^= (1 << pin); // Toggle pin
}

void initializeAnalogClock() {
    // Enable ADC1 clock
    RCC_APB2ENR |= (1 << 8); // ADC1EN
}

void turnOnADC() {
    ADC_CR2 |= (1 << 0); // ADON
}

void turnOffADC() {
    ADC_CR2 &= ~(1 << 0); // Clear ADON
}

void setADCSampleTime_Channel_6(const uint8_t sampleTime) {
    // Channel 6 is in SMPR2 (bits 20:18)

    // Values must be 3 bits
    
    // Clear existing sample time bits for channel 6
    ADC_SMPR2 &= ~(0x7 << 18);

    // Set new sample time
    ADC_SMPR2 |= (sampleTime << 18);
}

void setADCChannel(uint8_t channel) {
    // Set the first conversion in regular sequence to the specified channel
    ADC_SQR3 &= ~0x1F; // Clear bits 4:0
    ADC_SQR3 |= (channel); // Set channel
}

void setADCContinuousMode(bool enable) {
    if (enable) {
        ADC_CR2 |= (1 << 1); // CONT
    } else {
        ADC_CR2 &= ~(1 << 1); // Clear CONT
    }
}

void startADCConversion() {
    ADC_CR2 |= (1 << 30); // SWSTART
}

bool isADCConversionComplete() {
    return (ADC_SR & (1 << 1)) != 0; // EOC
}

uint16_t readADCData() {
    return ADC_DR;
}

void full_setup_adc_channel_6(uint8_t sampleTime) {
    setADCSampleTime_Channel_6(sampleTime);         // Sample Time 3 would be 56 cycles
    setADCChannel(6);
    setADCContinuousMode(true);
    turnOnADC();
    startADCConversion();
}