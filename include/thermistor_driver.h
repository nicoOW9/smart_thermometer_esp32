#ifndef THERMISTOR_H
#define THERMISTOR_H

#include <Arduino.h>
#include "thermistor_config.h"

#define PIN_ANALOG_IN 34

float readTemperature(); // °C * 10
int* splitTemperatureToDigits(float temperature); // returns 4-digit array

#endif
