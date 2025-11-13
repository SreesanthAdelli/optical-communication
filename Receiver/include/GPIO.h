// General purpose input/output (GPIO) definitions
#pragma once

#include <stdint.h>
#include <stdbool.h>

void initializeGPIOA();

void setPinOutput(uint8_t pin);

void setPin(uint8_t pin, bool value);

void togglePin(uint8_t pin);


