#ifndef CONFIG_H
#define CONFIG_H

#include <TFT_eSPI.h>

// ============================================================
// 3x0c3t BO4RD KEYPAD
// CONFIGURATION
// ESP8266 + TFT_eSPI + ILI9341 + XPT2046
// ============================================================

// ============================================================
// ÉCRAN
// ============================================================

#define SCREEN_WIDTH   240
#define SCREEN_HEIGHT  320

#define TFT_ROTATION   2

// ============================================================
// TOUCH
// ============================================================

#define CALIBRATION_FILE "/TouchCalData1"
#define REPEAT_CAL       false

// ============================================================
// PALETTE UI
// ============================================================
//
// Fond       : noir
// Panneau    : gris #20252A
// Texte      : blanc
// Secondaire : gris clair
// Accent     : cyan
// Valeur     : cyan
// OK         : vert
// Attention  : orange
// Erreur     : rouge
// Action     : bleu
//
// ============================================================

#define UI_BG               TFT_BLACK
#define UI_PANEL            0x2124

#define UI_TEXT             TFT_WHITE
#define UI_TEXT_SECONDARY   TFT_LIGHTGREY

#define UI_ACCENT           TFT_CYAN
#define UI_VALUE            TFT_CYAN

#define UI_OK               TFT_GREEN
#define UI_WARNING          TFT_ORANGE
#define UI_ERROR            TFT_RED

#define UI_ACTION           TFT_BLUE

// ============================================================
// COMPATIBILITÉ ANCIENS NOMS
// ============================================================
//
// Certaines parties du projet utilisent encore COLOR_*.
// On garde ces alias pour éviter que chaque fichier ait son
// propre dialecte de configuration.
//
// ============================================================

#define COLOR_BACKGROUND    UI_BG
#define COLOR_PANEL         UI_PANEL
#define COLOR_TEXT          UI_TEXT
#define COLOR_TEXT_DIM      UI_TEXT_SECONDARY
#define COLOR_ACCENT        UI_ACCENT
#define COLOR_VALUE         UI_VALUE
#define COLOR_OK            UI_OK
#define COLOR_WARNING       UI_WARNING
#define COLOR_ERROR         UI_ERROR
#define COLOR_ACTION        UI_ACTION

// ============================================================
// HEADER
// ============================================================

#define HEADER_X            8
#define HEADER_Y            5
#define HEADER_W            224
#define HEADER_H            24

// Ligne inférieure du header
#define HEADER_LINE_Y       31

// ============================================================
// ZONE D'AFFICHAGE
// ============================================================

#define DISPLAY_X           8
#define DISPLAY_Y           38
#define DISPLAY_W           224
#define DISPLAY_H           34

// Compatibilité ancien nom
#define DISP_X              DISPLAY_X
#define DISP_Y              DISPLAY_Y
#define DISP_W              DISPLAY_W
#define DISP_H              DISPLAY_H

#define DISP_TCOLOR         UI_VALUE

// ============================================================
// ZONE STATUS
// ============================================================
//
// Affichage : 38 -> 72
// Status    : 76 -> 88
// Boutons   : 92 ->
//
// ============================================================

#define STATUS_X            120
#define STATUS_Y            76
#define STATUS_W            224
#define STATUS_H            12

// ============================================================
// KEYPAD
// ============================================================

#define KEY_X               40
#define KEY_Y               92

#define KEY_W               64
#define KEY_H               34

#define KEY_SPACING_X       16
#define KEY_SPACING_Y       7

#define KEY_TEXTSIZE        1

// Police intégrée TFT_eSPI
#define KEY_FONT            2

// ============================================================
// INPUT
// ============================================================

#define NUM_LEN             12

// ============================================================
// TFT
// ============================================================

extern TFT_eSPI tft;

#endif