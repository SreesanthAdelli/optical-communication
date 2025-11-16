// GPIO pin control implementation

#include "GPIO.h"
#include "utilities.h"
#include <stdint.h>
#include <stdbool.h>

// STM32F446RE GPIO registers (AHB1 base)
#define RCC_AHB1ENR   (*(volatile uint32_t*)0x40023830)
#define GPIOA_MODER   (*(volatile uint32_t*)0x40020000)
#define GPIOA_ODR     (*(volatile uint32_t*)0x40020014)
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