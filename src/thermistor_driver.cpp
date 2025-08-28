#include "thermistor_driver.h"
#include <math.h>

float readTemperature() {
    int adcValue = analogRead(PIN_ANALOG_IN);
    double voltage = (float)adcValue / 4095.0 * 3.3;
    double Rt = 10 * voltage / (3.3 - voltage);
    Rt = Rt * THERMISTOR_CALIB_K;
    double tempK = 1 / (1 / (273.15 + 25) + log(Rt / 10) / 3950.0);
    double tempC = tempK - 273.15 + THERMISTOR_OFFSET;
    return tempC * 10; // tenths of °C
}

int* splitTemperatureToDigits(float temperature) {
    static int digits[4];
    int tempTenths = (int)round(temperature);
    digits[0] = tempTenths / 100;
    digits[1] = (tempTenths / 10) % 10;
    digits[2] = tempTenths % 10;
    digits[3] = 10; // "C"
    return digits;
}
