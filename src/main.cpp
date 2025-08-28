#include <Arduino.h>
#include "display_driver.h"
#include "thermistor_driver.h"
#include "wifi_driver.h"

void setup() {
    Serial.begin(115200);

    // Init display pins
    initDisplayPins();

    // Init thermistor pin
    pinMode(PIN_ANALOG_IN, INPUT);

    Serial.println("Thermistor Test");
    int connection_status=init_wifi();
    Serial.printf("WiFi connection status: %d\n", connection_status);
}

void loop() {
    
if (WiFi.status() != WL_CONNECTED) {
        Serial.println("Wi-Fi lost, reconnecting...");
        init_wifi();
    }
    // Read temperature 
    float tempC = readTemperature();
    Serial.printf("Temperature: %.2f C\n", tempC / 10);

    // Split temperature into digits
    int* digits = splitTemperatureToDigits(tempC);
    Serial.printf("Digits: %d,%d,%d,%d\n", digits[0], digits[1], digits[2], digits[3]);

    // Display digits with simple multiplexing
    for (int _i = 0; _i < 1000; _i++) {
        writeDigit(digits[0]);
        selectDigit(0);
        delay(DIGIT_REFRESH_DELAY_MS);

        writeDigitWithPoint(digits[1]); // decimal point on second digit
        selectDigit(1);
        delay(DIGIT_REFRESH_DELAY_MS);

        writeDigit(digits[2]);
        selectDigit(2);
        delay(DIGIT_REFRESH_DELAY_MS);

        writeDigit(digits[3]); // 'C'
        selectDigit(3);
        delay(DIGIT_REFRESH_DELAY_MS);
    }
}
