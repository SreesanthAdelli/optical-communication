// GPIO pin control implementation

#include "GPIO.h"
#include <stdint.h>
#include <stdbool.h>

// STM32F446RE GPIO registers (AHB1 base)
#define RCC_AHB1ENR   (*(volatile uint32_t*)0x40023830)
#define GPIOA_MODER   (*(volatile uint32_t*)0x40020000)
#define GPIOA_ODR     (*(volatile uint32_t*)0x40020014)


void initializeGPIOA() {
    // Enable GPIOA clock
    RCC_AHB1ENR |= (1 << 0); // GPIOAEN
}

void setPinOutput(uint8_t pin) {
    // Set specified pin as output (MODERx = 01)
    GPIOA_MODER &= ~(0x3 << (pin * 2)); // Clear mode bits
    GPIOA_MODER |=  (0x1 << (pin * 2)); // Set as output
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