// GPIO pin control implementation

#include "GPIO.h"
#include "utilities.h"
#include <stdint.h>
#include <stdbool.h>

// STM32F446RE GPIO registers (AHB1 base)
#define RCC_BASE      0x40023800
#define RCC_AHB1ENR   (*(volatile uint32_t*)(RCC_BASE + 0x30))
#define RCC_APB2ENR   (*(volatile uint32_t*)(RCC_BASE + 0x44))
#define GPIOA_MODER   (*(volatile uint32_t*)0x40020000)
#define GPIOA_ODR     (*(volatile uint32_t*)0x40020014)
#define ADC_BASE      0x40012000
#define ADC_CR2       (*(volatile uint32_t*)(ADC_BASE + 0x08))
#define ADC_SMPR1     (*(volatile uint32_t*)(ADC_BASE + 0x0C))
#define ADC_SMPR2     (*(volatile uint32_t*)(ADC_BASE + 0x10))
#define ADC_SQR3      (*(volatile uint32_t*)(ADC_BASE + 0x34))
#define ADC_SR        (*(volatile uint32_t*)(ADC_BASE + 0x00))
#define ADC_DR        (*(volatile uint32_t*)(ADC_BASE + 0x4C))
#define ONE_SECOND    2000000  // 1 second at 2 MHz clock


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

void flashPin_10(uint8_t pin) {
    togglePin(pin);
    delay(0.1 * ONE_SECOND);
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