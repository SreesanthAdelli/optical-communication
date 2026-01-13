#include "pwm.h"


void pwmInit_pa5(void)
{
    // 1. Enable clocks
    RCC_AHB1ENR |= (1 << 0);   // GPIOAEN
    RCC_APB1ENR |= (1 << 0);   // TIM2EN

    // 2. Configure PA5 as Alternate Function (AF1 = TIM2_CH1)
    GPIOA_MODER &= ~(3 << (5*2));
    GPIOA_MODER |=  (2 << (5*2));   // AF mode
    GPIOA_AFRL &= ~(0xF << (5*4));
    GPIOA_AFRL |=  (1 << (5*4));    // AF1

    // 3. Timer base: 1 MHz timer clock
    // TIM2 clock = 20 MHz / (PSC+1) = 1 MHz → PSC = 19
    TIM2_PSC = 20 - 1;

    // 4. Default frequency = 1 kHz → ARR = timer_clk / freq -1 = 1MHz/1kHz-1 = 999
    TIM2_ARR = 999;
    TIM2_CCR1 = 50; // 50% duty

    // 5. PWM mode 1, preload enable
    TIM2_CCMR1 &= ~(7 << 4);
    TIM2_CCMR1 |=  (6 << 4);  // PWM mode 1
    TIM2_CCMR1 |=  (1 << 3);    // OC1PE

    // 6. Enable channel
    TIM2_CCER |= (1 << 0);       // CC1E

    // 7. Auto-reload preload
    TIM2_CR1 |= (1 << 7);        // ARPE

    // 8. Start timer
    TIM2_CR1 |= (1 << 0);        // CEN
}


void setPWMFrequency_pa5(uint32_t frequency)
{
    if (frequency == 0) {
        TIM2_CCR1 = 0; // 0% duty cycle
        return;
    }

    uint32_t arr = 1000000 / frequency - 1; // ARR for desired frequency
    TIM2_ARR = arr;

    // Maintain 50% duty cycle
    TIM2_CCR1 = (arr + 1) / 2;
}
