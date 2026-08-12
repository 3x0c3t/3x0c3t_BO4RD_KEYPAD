// settings.h
#ifndef SETTINGS_H
#define SETTINGS_H

#include <Arduino.h>

// ============================================================
// 3x0c3t BO4RD KEYPAD v1.0
// ESP8266 + ILI9341 + XPT2046
// ============================================================

// ============================================================
// TFT
// ============================================================

#define TFT_WIDTH     240
#define TFT_HEIGHT    320
#define TFT_ROTATION  2

#define TFT_CS   15   // D8
#define TFT_DC    2   // D4
#define TFT_RST  16   // D0

// ============================================================
// TOUCH
// ============================================================

#define TOUCH_CS   0   // D3
#define TOUCH_IRQ  5   // D1

// ============================================================
// SPI
// ============================================================

#define SPI_SCK   14   // D5
#define SPI_MISO  12   // D6
#define SPI_MOSI  13   // D7

// ============================================================
// COULEURS RGB565
// ============================================================

#define COLOR_BG          0x1082
#define COLOR_HEADER      0x2124
#define COLOR_RESULT      0x0000

#define COLOR_KEY         0x39C7
#define COLOR_KEY_ALT     0x528A
#define COLOR_KEY_PRESS   0x07E0

#define COLOR_TEXT        0xFFFF
#define COLOR_TEXT_ALT    0xFFE0
#define COLOR_ACCENT      0x07FF

#define COLOR_BORDER      0x8410
#define COLOR_SEPARATOR   0x630C

// ============================================================
// ZONE RESULTAT
// ============================================================

#define RESULT_X          8
#define RESULT_Y          8
#define RESULT_W          224
#define RESULT_H          48

// ============================================================
// CLAVIER
// ============================================================

#define KEY_COLS          3
#define KEY_ROWS          5

#define KEY_W             62
#define KEY_H             28

#define KEY_GAP_X         8
#define KEY_GAP_Y         5

#define KEY_START_X       8
#define KEY_START_Y       68

// ============================================================
// TEXTE
// ============================================================

#define RESULT_TEXT_SIZE  3
#define KEY_TEXT_SIZE     2

#endif