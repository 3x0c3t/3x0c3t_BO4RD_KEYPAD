#ifndef KEYPAD_H
#define KEYPAD_H

#include <TFT_eSPI.h>

extern TFT_eSPI_Button key[15];

extern char keyLabel[15][5];

extern uint16_t keyColor[15];

void drawKeypad();

void status(const char *msg);

#endif