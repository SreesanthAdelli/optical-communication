#pragma once

#define TIM5_BASE       0x40000C00UL                                            // TIM5 Base Address 
#define TIM5_CR1        (*(volatile uint32_t *)(TIM5_BASE + 0x00))              // TIM5 Control Register
#define TIM5_EGR        (*(volatile uint32_t *)(TIM5_BASE + 0x14))              // TIM5 Event Generation Register
#define TIM5_CNT        (*(volatile uint32_t *)(TIM5_BASE + 0x24))              // TIM5 Counter Register
#define TIM5_PSC        (*(volatile uint32_t *)(TIM5_BASE + 0x28))              // TIM5 Prescaler Register
#define TIM5_ARR        (*(volatile uint32_t *)(TIM5_BASE + 0x2C))              // TIM5 Auto-Reload Register

#define GPIOA_BASE      0x40020000UL                                            // GPIOA Base Address
#define GPIOA_MODER     (*(volatile uint32_t*)(GPIOA_BASE + 0x00))              // GPIOA Mode Register
#define GPIOA_ODR       (*(volatile uint32_t*)(GPIOA_BASE + 0x14))              // GPIOA Output Data Register   
#define GPIOA_AFRL      (*(volatile uint32_t*)(GPIOA_BASE + 0x20))              // GPIOA Alternate Function Low Register

#define ADC_BASE        0x40012000UL                                            // ADC1 Base Address
#define ADC_CR2         (*(volatile uint32_t*)(ADC_BASE + 0x08))                // ADC Control Register 2
#define ADC_SMPR1       (*(volatile uint32_t*)(ADC_BASE + 0x0C))                // ADC Sample Time Register 1
#define ADC_SMPR2       (*(volatile uint32_t*)(ADC_BASE + 0x10))                // ADC Sample Time Register 2
#define ADC_SQR3        (*(volatile uint32_t*)(ADC_BASE + 0x34))                // ADC Regular Sequence Register 3
#define ADC_SR          (*(volatile uint32_t*)(ADC_BASE + 0x00))                // ADC Status Register
#define ADC_DR          (*(volatile uint32_t*)(ADC_BASE + 0x4C))                // ADC Data Register

#define RCC_BASE        0x40023800UL                                            // RCC Base Address
#define RCC_CR          (*(volatile uint32_t*)(RCC_BASE + 0x00))                // RCC Clock Control Register
#define RCC_PLLCFGR     (*(volatile uint32_t*)(RCC_BASE + 0x04))                // RCC PLL Configuration Register
#define RCC_CFGR        (*(volatile uint32_t*)(RCC_BASE + 0x08))                // RCC Clock Configuration Register
#define RCC_AHB1ENR     (*(volatile uint32_t*)(RCC_BASE + 0x30))                // RCC AHB1 Peripheral Clock Enable Register
#define RCC_APB2ENR     (*(volatile uint32_t*)(RCC_BASE + 0x44))                // RCC APB2 Peripheral Clock Enable Register
#define RCC_APB1ENR     (*(volatile uint32_t*)(RCC_BASE + 0x40))                // RCC APB1 Peripheral Clock Enable Register


#define FLASH_BASE      0x40023C00UL                                            // FLASH Base Address
#define FLASH_ACR       (*(volatile uint32_t*)(FLASH_BASE + 0x00))              // FLASH Access Control Register

#define TIM2_BASE      0x40000000UL                                            // TIM2 Base Address
#define TIM2_CR1       (*(volatile uint32_t*)0x40000000)
#define TIM2_CCMR1     (*(volatile uint32_t*)0x40000018)
#define TIM2_CCER      (*(volatile uint32_t*)0x40000020)
#define TIM2_PSC       (*(volatile uint32_t*)0x40000028)
#define TIM2_ARR       (*(volatile uint32_t*)0x4000002C)
#define TIM2_CCR1      (*(volatile uint32_t*)0x40000034)






