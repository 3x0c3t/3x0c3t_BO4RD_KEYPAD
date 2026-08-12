#ifndef CONFIG_H
#define CONFIG_H

#include <TFT_eSPI.h>
#include <FS.h>

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 320

#define TFT_ROTATION 2

#define CALIBRATION_FILE "/TouchCalData1"
#define REPEAT_CAL false

#define UI_BG TFT_BLACK
#define UI_PANEL TFT_DARKGREY
#define UI_TEXT TFT_WHITE
#define UI_TEXT_SECONDARY TFT_LIGHTGREY
#define UI_ACCENT TFT_CYAN
#define UI_VALUE TFT_CYAN
#define UI_OK TFT_GREEN
#define UI_WARNING TFT_ORANGE
#define UI_ERROR TFT_RED
#define UI_ACTION TFT_BLUE

#define DISPLAY_X 8
#define DISPLAY_Y 8
#define DISPLAY_W 224
#define DISPLAY_H 42

#define STATUS_X 120
#define STATUS_Y 55

#define KEY_AREA_Y 76
#define KEY_W 62
#define KEY_H 38
#define KEY_SPACING_X 7
#define KEY_SPACING_Y 7

#define KEY_X 40
#define KEY_Y KEY_AREA_Y

#define KEY_TEXTSIZE 1

#define LABEL1_FONT &FreeSansBold12pt7b
#define LABEL2_FONT &FreeSansBold12pt7b

#define NUM_LEN 12

extern TFT_eSPI tft;

#endif