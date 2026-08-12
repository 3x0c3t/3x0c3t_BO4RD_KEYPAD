#ifndef KEYPAD_H
#define KEYPAD_H

#include <Arduino.h>
#include <TFT_eSPI.h>

void initKeypad();
void drawKeypad();
void updateKeypad(uint16_t t_x, uint16_t t_y, bool pressed);
void updateDisplay();
void status(const char *msg);

#endif