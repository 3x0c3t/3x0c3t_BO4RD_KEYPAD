#ifndef SETTINGS_H
#define SETTINGS_H

#include <Arduino.h>
#include <TFT_eSPI.h>

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 320

#define TFT_ROTATION 2

#define SERIAL_BAUD 115200

#define CALIBRATION_FILE "/TouchCalData1"

#define REPEAT_CAL false

#define COLOR_BACKGROUND TFT_BLACK
#define COLOR_PANEL TFT_DARKGREY
#define COLOR_BORDER TFT_DARKGREY
#define COLOR_TEXT TFT_WHITE
#define COLOR_ACCENT TFT_GREEN
#define COLOR_TOUCH TFT_RED
#define COLOR_NUMBER TFT_CYAN

#define HEADER_X 0
#define HEADER_Y 0
#define HEADER_W SCREEN_WIDTH
#define HEADER_HEIGHT 32

#define VALUE_X 10
#define VALUE_Y 42
#define VALUE_W 220
#define VALUE_HEIGHT 48

#define KEY_COUNT 15

#define KEY_W 60
#define KEY_H 38

#define KEY_SPACING_X 10
#define KEY_SPACING_Y 10

#define KEY_START_X 15
#define KEY_START_Y 100

#define NUM_LEN 12

#endif