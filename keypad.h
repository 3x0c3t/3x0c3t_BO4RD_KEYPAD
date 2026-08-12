#ifndef KEYPAD_MODULE_H
#define KEYPAD_MODULE_H

#include <Arduino.h>

void keypadInit();
void keypadLoop();

void drawKeypad();

void handleKey(
    uint8_t index
);

const char *getNumberBuffer();

#endif