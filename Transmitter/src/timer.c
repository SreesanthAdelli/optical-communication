#include <stdint.h>
#include "stm32f446xx.h"
#include "timer.h"

void startTimer(){
    RCC_APB1ENR |= (1 << 3);    // Enable TIM5 clock
    TIM5_PSC = 19;              // Set prescaler to 1/20
    TIM5_ARR = 0xFFFFFFFF;      // Set auto-reload to max
    TIM5_EGR |= 1;              // Generate an update event to load the prescaler value
    TIM5_CR1 = 1;               // Start counter
}


uint64_t getTicks() {

    static uint16_t last_cnt = 0;
    static uint64_t total_cnt = 0;

    uint16_t current_cnt = TIM5_CNT;

    if (current_cnt >= last_cnt) {
        total_cnt += (current_cnt - last_cnt);              // No overflow
    } else {
        total_cnt += (0xFFFF - last_cnt + 1 + current_cnt); // Handle overflow
    }

    last_cnt = current_cnt;
    return total_cnt;                                       // Return total ticks
}
