#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

void displayInit();

void displayClear();

void displayDrawHeader();

void displayDrawResult(
    const String &value
);

void displayDrawKey(
    int x,
    int y,
    int w,
    int h,
    const String &label,
    uint16_t color,
    uint16_t textColor
);

void displayDrawKeyboard();

#endif