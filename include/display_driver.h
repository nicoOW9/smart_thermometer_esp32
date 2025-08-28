#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include "display_config.h"

// Pins
#define LATCHPIN 2
#define CLOCKPIN 4
#define DATAPIN 15
extern const int DIGIT_PINS[4];

// Segment mapping
extern const byte digitToSegments[11];
extern const byte digitPointToSegments[11];

// Functions
void initDisplayPins();
void writeDigit(int digit);
void writeDigitWithPoint(int digit);
void selectDigit(int digit);

#endif
