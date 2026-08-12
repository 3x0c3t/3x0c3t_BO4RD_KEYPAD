#ifndef KEYPAD_H
#define KEYPAD_H

#include <Arduino.h>
#include <TFT_eSPI.h>

void drawKeypad();
void updateKeypad(uint16_t t_x, uint16_t t_y, bool pressed);
void handleKey(uint8_t b);
void updateDisplay();
void status(const char *msg);

extern TFT_eSPI_Button key[15];

extern char numberBuffer[];
extern uint8_t numberIndex;

#endif