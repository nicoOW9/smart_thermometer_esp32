#include <Arduino.h>
#include "display_driver.h"
#include "thermistor_driver.h"
#include "wifi_driver.h"
#include "button_driver.h"
#include <HTTPClient.h>
#include <ArduinoJson.h>

bool showOutside = false;

void setup() {
    Serial.begin(115200);

    // Init display pins
    initDisplayPins();

    // Init thermistor pin
    pinMode(PIN_ANALOG_IN, INPUT);
    pinMode(21,OUTPUT);
    Serial.println("Thermistor Test");
    int connection_status=init_wifi();
    Serial.printf("WiFi connection status: %d\n", connection_status);
}

void loop() {
    
if (WiFi.status() != WL_CONNECTED) {
        Serial.println("Wi-Fi lost, reconnecting...");
        init_wifi();
    }
    float outside_temp=getOutsideTemperature();
    Serial.printf("Outside Temperature: %.2f C\n", outside_temp);
    // Read temperature 
    float tempC = readTemperature();
    Serial.printf("Temperature: %.2f C\n", tempC / 10);

    // Split temperature into digits
    int* digits = splitTemperatureToDigits(tempC);
    Serial.printf("Digits: %d,%d,%d,%d\n", digits[0], digits[1], digits[2], digits[3]);
    
    if(outside_temp<tempC){
        digitalWrite(21,HIGH);
    }
    else{
        digitalWrite(21,LOW);
    }

    // Display digits with simple multiplexing
    for (int _i = 0; _i < 10000; _i++) {
        
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
        if(checkButtonToggle()){
            Serial.println("Button toggled!");
            showOutside = !showOutside;
        }
        if(showOutside){
            int* digits = splitTemperatureToDigits(outside_temp*10);
            
        }
        else{
            int* digits = splitTemperatureToDigits(tempC);}

    }
}
