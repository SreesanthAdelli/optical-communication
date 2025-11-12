#include "GPIO.h"
#include "utilities.h"
#include <stdint.h>
#include <stdbool.h>
#define PA6           5

// 2 MHz clock

int main(void)
{

    // Enable GPIOA clock
    initializeGPIOA();

    // Configure PA6 as output (Laser control)
    setPinOutput(PA6);

    // Set PA6 high to turn on Laser
    setPin(PA6, true);

    while(1) {
        // Toggle PA6 - GPIO for Laser
        togglePin(PA6);
        delay(2000000);                                 
    }

    return 0; // Never reached
}
