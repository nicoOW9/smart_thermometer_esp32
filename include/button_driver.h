#include <Arduino.h>
#define debouncetimer 50
#define BUTTONPIN 13            // the current reading from the input pin
   // the previous reading from the input pin

bool checkButtonToggle();
void initButton();