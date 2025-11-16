// General purpose input/output (GPIO) definitions
#pragma once

#include "utilities.h"
#include <stdint.h>
#include <stdbool.h>

void initializeGPIOA();

void setPinDigitalOutput(uint8_t pin);

void setPinAnalog(uint8_t pin);

void setPin(uint8_t pin, bool value);

void togglePin(uint8_t pin);

void flashPin_10(uint8_t pin);
