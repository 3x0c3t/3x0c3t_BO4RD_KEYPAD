#ifndef CONFIG_H
#define CONFIG_H

#include <TFT_eSPI.h>
#include <FS.h>
#include <LittleFS.h>

// ============================================================
// TFT
// ============================================================

#define SCREEN_WIDTH  240
#define SCREEN_HEIGHT 320

#define TFT_ROTATION 2

// ============================================================
// TOUCH
// ============================================================

#define CALIBRATION_FILE "/TouchCalData1"
#define REPEAT_CAL false

// ============================================================
// COULEURS UI
// ============================================================

#define UI_BG              TFT_BLACK
#define UI_PANEL           TFT_DARKGREY
#define UI_TEXT            TFT_WHITE
#define UI_TEXT_SECONDARY  TFT_LIGHTGREY
#define UI_ACCENT          TFT_CYAN
#define UI_VALUE           TFT_CYAN
#define UI_OK              TFT_GREEN
#define UI_WARNING         TFT_ORANGE
#define UI_ERROR           TFT_RED
#define UI_ACTION          TFT_BLUE

// Compatibilité avec KEYPAD.ino
#define COLOR_BACKGROUND   UI_BG
#define COLOR_PANEL        UI_PANEL
#define COLOR_TEXT         UI_TEXT
#define COLOR_TEXT_DIM     UI_TEXT_SECONDARY
#define COLOR_ACCENT       UI_ACCENT
#define COLOR_VALUE        UI_VALUE
#define COLOR_OK           UI_OK
#define COLOR_WARNING      UI_WARNING
#define COLOR_ERROR        UI_ERROR
#define COLOR_ACTION       UI_ACTION

// ============================================================
// HEADER
// ============================================================

#define HEADER_X           0
#define HEADER_Y           0
#define HEADER_W           SCREEN_WIDTH
#define HEADER_H           30

#define HEADER_LINE_Y      30

// ============================================================
// ZONE D'AFFICHAGE DE LA TOUCHE
// ============================================================

#define DISPLAY_X          8
#define DISPLAY_Y          38
#define DISPLAY_W          224
#define DISPLAY_H          34

// Compatibilité ancien code
#define DISP_X              DISPLAY_X
#define DISP_Y              DISPLAY_Y
#define DISP_W              DISPLAY_W
#define DISP_H              DISPLAY_H

// ============================================================
// KEYPAD
// ============================================================

#define KEY_COLS            3
#define KEY_ROWS            4

#define KEY_W               64
#define KEY_H               34

#define KEY_GAP_X           12
#define KEY_GAP_Y           10

// Largeur réelle de la grille
#define KEYPAD_W \
    ((KEY_COLS * KEY_W) + ((KEY_COLS - 1) * KEY_GAP_X))

// Centrage automatique sur 240 px
#define KEYPAD_X \
    ((SCREEN_WIDTH - KEYPAD_W) / 2)

#define KEYPAD_Y            92

// ============================================================
// TOUCH / STATUS
// ============================================================

#define STATUS_X            (SCREEN_WIDTH / 2)
#define STATUS_Y            310

#define STATUS_W            220
#define STATUS_H            18

// ============================================================
// BOUTONS
// ============================================================

#define KEY_TEXTSIZE        1

// Nombre total de touches
#define NUM_KEYS            12

// ============================================================
// FONTS
// ============================================================

// Police TFT_eSPI intégrée.
// On évite les FreeFonts externes ici pour garder le projet
// compilable sans dépendance supplémentaire.

#define KEY_FONT_SIZE       2

// ============================================================
// TFT GLOBAL
// ============================================================

extern TFT_eSPI tft;

#endif