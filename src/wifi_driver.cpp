#include "wifi_driver.h"
#include <WiFi.h>
#include <Arduino.h>
#include "secrets.h"
#include <HTTPClient.h>
#include <ArduinoJson.h>


int init_wifi(){
    const int wifidebugpin=WIFIDEBUGPIN;
    const char* wifi_ssid=WIFI_SSID;
    const char* wifi_password=WIFI_PASSWORD;
    const int wifi_waittime=WIFI_WAITTIME;
    pinMode(wifidebugpin, OUTPUT);
    digitalWrite(wifidebugpin, LOW);  
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    delay(wifi_waittime);
    for(int i=0; i<10; i++){
        if (WiFi.status()==WL_CONNECTED) break;
        delay(wifi_waittime);
        digitalWrite(wifidebugpin, LOW);   // turn the LED on (HIGH is the voltage level)
        delay(wifi_waittime);
        digitalWrite(wifidebugpin, HIGH);   // turn the LED on (HIGH is the voltage level)
    }
    if(WiFi.status()!=WL_CONNECTED){
        digitalWrite(wifidebugpin, LOW);   // turn the LED on (HIGH is the voltage level)
        return 0;
    } 
   else{
        digitalWrite(wifidebugpin, HIGH);   // turn the LED on (HIGH is the voltage level)
        return 1;
    }

}

float getOutsideTemperature() {
    if (WiFi.status() != WL_CONNECTED) return NAN;

    HTTPClient http;
    String url = String("http://api.weatherapi.com/v1/current.json?key=") +WEATHER_API_KEY+"&q="+ lattitude +"," + Longitude;

    http.begin(url);
    int httpCode = http.GET();

    float temp_c = NAN;

    if (httpCode == 200) {
        String payload = http.getString();
        DynamicJsonDocument doc(1024);
        deserializeJson(doc, payload);
        temp_c = doc["current"]["temp_c"];   // °C
    } else {
        Serial.printf("HTTP GET failed, code: %d\n", httpCode);
    }

    http.end();
    return temp_c;
}