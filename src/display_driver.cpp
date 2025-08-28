#include "display_driver.h"

const int DIGIT_PINS[4] = {26, 25, 32, 33};

const byte digitToSegments[11] = {
    0b11110011, // 0
    0b10000010, // 1
    0b00110111, // 2
    0b10010111, // 3
    0b11000110, // 4
    0b11010101, // 5
    0b11110101, // 6
    0b10000011, // 7
    0b11110111, // 8
    0b11010111, // 9
    0b01110001, // C
};

const byte digitPointToSegments[11] = {
    digitToSegments[0] | 0b00001000,
    digitToSegments[1] | 0b00001000,
    digitToSegments[2] | 0b00001000,
    digitToSegments[3] | 0b00001000,
    digitToSegments[4] | 0b00001000,
    digitToSegments[5] | 0b00001000,
    digitToSegments[6] | 0b00001000,
    digitToSegments[7] | 0b00001000,
    digitToSegments[8] | 0b00001000,
    digitToSegments[9] | 0b00001000,
    digitToSegments[10] | 0b00001000,
};

void initDisplayPins() {
    for (int i = 0; i < 4; i++) pinMode(DIGIT_PINS[i], OUTPUT);
    pinMode(LATCHPIN, OUTPUT);
    pinMode(CLOCKPIN, OUTPUT);
    pinMode(DATAPIN, OUTPUT);
    digitalWrite(LATCHPIN, LOW);
    digitalWrite(CLOCKPIN, LOW);
    digitalWrite(DATAPIN, LOW);
}

void shiftRegisterInit() {
    digitalWrite(LATCHPIN, LOW);
    digitalWrite(CLOCKPIN, LOW);
    digitalWrite(DATAPIN, LOW);
}

void writeDigit(int digit) {
    shiftRegisterInit();
    byte data = digitToSegments[digit];
    for (int i = 0; i < 8; i++) {
        digitalWrite(DATAPIN, (~data >> i) & 0b01);
        digitalWrite(CLOCKPIN, HIGH);
        digitalWrite(CLOCKPIN, LOW);
    }
    digitalWrite(LATCHPIN, HIGH);
}

void writeDigitWithPoint(int digit) {
    shiftRegisterInit();
    byte data = digitPointToSegments[digit];
    for (int i = 0; i < 8; i++) {
        digitalWrite(DATAPIN, (~data >> i) & 0b01);
        digitalWrite(CLOCKPIN, HIGH);
        digitalWrite(CLOCKPIN, LOW);
    }
    digitalWrite(LATCHPIN, HIGH);
}

void selectDigit(int digit) {
    for (int i = 0; i < 4; i++) digitalWrite(DIGIT_PINS[i], LOW);
    digitalWrite(DIGIT_PINS[digit], HIGH);
}
