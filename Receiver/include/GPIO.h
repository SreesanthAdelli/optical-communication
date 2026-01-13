// General purpose input/output (GPIO) definitions
#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "stm32f446xx.h"

void initializeGPIOA();
void setPinDigitalOutput(uint8_t pin);
void setPinAnalog(uint8_t pin);
void setPin(uint8_t pin, bool value);
void togglePin(uint8_t pin);
void flashPin_10(uint8_t pin);
void initializeAnalogClock();
void turnOnADC();
void turnOffADC();
void setADCSampleTime_Channel_6(const uint8_t sampleTime);
void setADCChannel(uint8_t channel);
void setADCContinuousMode(bool enable);
void startADCConversion();
bool isADCConversionComplete();
uint16_t readADCData();

void full_setup_adc_channel_6(uint8_t sampleTime);