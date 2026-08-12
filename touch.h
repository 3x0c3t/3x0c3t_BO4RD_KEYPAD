#ifndef TOUCH_MODULE_H
#define TOUCH_MODULE_H

#include <Arduino.h>

void touchInit();

bool touchRead(
    uint16_t &x,
    uint16_t &y
);

#endif