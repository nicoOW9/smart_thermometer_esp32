#include "button_driver.h"
#include <Arduino.h>



// internal static variables so they stay local to this file
static int lastState = HIGH;    // assuming INPUT_PULLUP
static int changeCount = 0;

void initButton() {
    
    pinMode(BUTTONPIN, INPUT_PULLUP);  // one side of button -> GND
}

bool checkButtonToggle() {
    static int lastState = HIGH;   // default not pressed
    static int changeCount = 0;
    int currentState = digitalRead(BUTTONPIN);

    if (currentState != lastState) {
        delay(5); // debounce ~5ms
        if (digitalRead(BUTTONPIN) == currentState) {
            changeCount++;
            lastState = currentState;
        }
    }

    if (changeCount >= 2) {
        changeCount = 0;
        return true; // toggle condition met
    }
    return false;
}