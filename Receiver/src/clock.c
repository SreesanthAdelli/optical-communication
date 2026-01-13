#include <stdint.h>
#include "stm32f446xx.h"
#include "clock.h"


void systemClock_20MHz(void) {
    // Enable HSE (High-Speed External) oscillator. HSE is 8 MHz on the Nucleo-F446RE board.
    RCC_CR |= (1 << 16); // HSEON

    // Wait until HSE is ready
    while (!(RCC_CR & (1 << 17)));

    // Configure the PLL for 20 MHz = 8 MHz / 8 * 160 / 8
    RCC_PLLCFGR =   (8 << 0)   |  // PLLM = 8
                    (160 << 6) |  // PLLN = 160
                    (3 << 16) |   // PLLP = /8 (encoded as 3)
                    (7 << 24) |   // PLLQ = 7 (USB unused)
                    (1 << 22);    // PLLSRC = HSE

                    
    // Enable the PLL
    RCC_CR |= (1 << 24); // PLLON

    // Wait until PLL is ready
    while (!(RCC_CR & (1 << 25)));

    // Select PLL as system clock source
    RCC_CFGR |= (2 << 0); // SW = 10 (PLL)

    // Wait until PLL is used as system clock source
    while ((RCC_CFGR & (3 << 2)) != (2 << 2));

}