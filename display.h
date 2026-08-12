#ifndef DISPLAY_MODULE_H
#define DISPLAY_MODULE_H

#include <Arduino.h>
#include <TFT_eSPI.h>

extern TFT_eSPI tft;

void drawCalibrationScreen();
void drawCalibrationComplete();

void drawInterface();
void drawHeader();
void drawValueDisplay();
void updateDisplay();
void drawStatus(const char *msg);

#endif