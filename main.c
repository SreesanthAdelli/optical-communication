#include <stdint.h>

// STM32F446RE GPIO registers (AHB1 base)
#define RCC_AHB1ENR   (*(volatile uint32_t*)0x40023830)
#define GPIOA_MODER   (*(volatile uint32_t*)0x40020000)
#define GPIOA_ODR     (*(volatile uint32_t*)0x40020014)

#define LED_PIN       5
#define PA6           6

// Simple delay function
void delay(volatile uint32_t count) {
    while(count--) ;
}

int main(void)
{
    // 1. Enable GPIOA clock
    RCC_AHB1ENR |= (1 << 0); // GPIOAEN

    // 2. Set PA5 as output (MODER5 = 01)
    GPIOA_MODER &= ~(0x3 << (LED_PIN * 2)); // Clear mode bits
    GPIOA_MODER |=  (0x1 << (LED_PIN * 2)); // Set as output

    GPIOA_MODER &= ~(0x3 << (PA6 * 2)); // Clear mode bits for PA6
    GPIOA_MODER |=  (0x1 << (PA6 * 2)); // Set PA6 as output

    GPIOA_ODR ^= (1 << LED_PIN);


    while(1) {
        // Toggle PA6 - GPIO for Laser
        GPIOA_ODR ^= (1 << PA6); // Toggle PA6
        delay(2000000);                                 
    }

    return 0; // Never reached
}
