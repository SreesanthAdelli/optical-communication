#pragma once
#include <stdint.h>
#include "stm32f446xx.h"


void pwmInit_pa5(void);

void setPWMFrequency_pa5(uint32_t frequency);