#ifndef WIFI_DRIVER_H
#define WIFI_DRIVER_H

#include <WiFi.h>
#define WIFIDEBUGPIN 22
#define WIFI_WAITTIME 3000  // in milliseconds

// WiFi network credentials

int init_wifi();
float getOutsideTemperature();
#endif