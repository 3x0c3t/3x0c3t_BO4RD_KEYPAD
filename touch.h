#ifndef TOUCH_H
#define TOUCH_H

#include <Arduino.h>

void touchInit();

bool touchAvailable();

bool touchRead(
    int16_t &x,
    int16_t &y
);

#endif