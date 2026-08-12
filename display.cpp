#include "display.h"
#include "settings.h"

// ============================================================
// TFT
// ============================================================

Adafruit_ILI9341 tft(
    TFT_CS,
    TFT_DC,
    TFT_RST
);

// ============================================================
// INITIALISATION
// ============================================================

void displayInit()
{
    tft.begin();

    tft.setRotation(TFT_ROTATION);

    tft.fillScreen(COLOR_BG);

    displayDrawHeader();
    displayDrawKeyboard();
}

// ============================================================
// ECRAN VIDE
// ============================================================

void displayClear()
{
    tft.fillScreen(COLOR_BG);
}

// ============================================================
// ZONE RESULTAT
// ============================================================

void displayDrawHeader()
{
    // Zone complète
    tft.fillRoundRect(
        RESULT_X,
        RESULT_Y,
        RESULT_W,
        RESULT_H,
        4,
        COLOR_RESULT
    );

    // Bordure
    tft.drawRoundRect(
        RESULT_X,
        RESULT_Y,
        RESULT_W,
        RESULT_H,
        4,
        COLOR_BORDER
    );

    // Petit titre
    tft.setTextColor(COLOR_ACCENT);
    tft.setTextSize(1);

    tft.setCursor(
        RESULT_X + 6,
        RESULT_Y + 5
    );

    tft.print("RESULTAT");
}

// ============================================================
// AFFICHAGE RESULTAT
// ============================================================

void displayDrawResult(const String &value)
{
    // Efface uniquement la partie valeur
    tft.fillRect(
        RESULT_X + 3,
        RESULT_Y + 18,
        RESULT_W - 6,
        RESULT_H - 21,
        COLOR_RESULT
    );

    tft.setTextColor(COLOR_TEXT);
    tft.setTextSize(RESULT_TEXT_SIZE);

    int16_t x1;
    int16_t y1;

    uint16_t w;
    uint16_t h;

    tft.getTextBounds(
        value,
        0,
        0,
        &x1,
        &y1,
        &w,
        &h
    );

    int16_t x =
        RESULT_X +
        (RESULT_W - w) / 2;

    int16_t y =
        RESULT_Y +
        RESULT_H -
        h -
        5;

    tft.setCursor(x, y);

    tft.print(value);
}

// ============================================================
// DESSIN D'UNE TOUCHE
// ============================================================

void displayDrawKey(
    int x,
    int y,
    int w,
    int h,
    const String &label,
    uint16_t color,
    uint16_t textColor
)
{
    // Fond
    tft.fillRoundRect(
        x,
        y,
        w,
        h,
        4,
        color
    );

    // Bordure
    tft.drawRoundRect(
        x,
        y,
        w,
        h,
        4,
        COLOR_BORDER
    );

    // Texte
    tft.setTextColor(textColor);
    tft.setTextSize(KEY_TEXT_SIZE);

    int16_t x1;
    int16_t y1;

    uint16_t tw;
    uint16_t th;

    tft.getTextBounds(
        label,
        0,
        0,
        &x1,
        &y1,
        &tw,
        &th
    );

    int16_t tx =
        x +
        (w - tw) / 2;

    int16_t ty =
        y +
        (h - th) / 2 -
        y1;

    tft.setCursor(tx, ty);

    tft.print(label);
}

// ============================================================
// CLAVIER
// ============================================================

void displayDrawKeyboard()
{
    const char *keys[KEY_ROWS][KEY_COLS] =
    {
        { "1", "2", "3" },
        { "4", "5", "6" },
        { "7", "8", "9" },
        { "*", "0", "#" },
        { "C", "OK", "<" }
    };

    for (int row = 0; row < KEY_ROWS; row++)
    {
        for (int col = 0; col < KEY_COLS; col++)
        {
            int x =
                KEY_START_X +
                col * (KEY_W + KEY_GAP_X);

            int y =
                KEY_START_Y +
                row * (KEY_H + KEY_GAP_Y);

            uint16_t color = COLOR_KEY;
            uint16_t textColor = COLOR_TEXT;

            // Ligne de fonctions
            if (row == 4)
            {
                color = COLOR_KEY_ALT;
                textColor = COLOR_TEXT_ALT;
            }

            displayDrawKey(
                x,
                y,
                KEY_W,
                KEY_H,
                keys[row][col],
                color,
                textColor
            );
        }
    }
}