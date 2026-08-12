// keypad.h
#ifndef KEYPAD_H
#define KEYPAD_H

#include <Arduino.h>

void keypadInit();

void keypadUpdate();

String keypadGetValue();

void keypadClear();

#endif