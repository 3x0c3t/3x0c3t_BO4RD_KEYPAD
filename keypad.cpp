#include "keypad.h"
#include "config.h"

// ============================================================
// LABELS
// ============================================================

static const char *keyLabel[NUM_KEYS] = {
    "New",
    "Del",
    "Send",

    "1",
    "2",
    "3",

    "4",
    "5",
    "6",

    "7",
    "8",
    "9"
};

// ============================================================
// POSITIONS DES BOUTONS
// ============================================================

static int16_t keyX[NUM_KEYS];
static int16_t keyY[NUM_KEYS];

// ============================================================
// INITIALISATION DES POSITIONS
// ============================================================

static void calculateKeyPositions()
{
    for (uint8_t row = 0; row < KEY_ROWS; row++)
    {
        for (uint8_t col = 0; col < KEY_COLS; col++)
        {
            uint8_t index = row * KEY_COLS + col;

            if (index >= NUM_KEYS)
                continue;

            keyX[index] =
                KEYPAD_X +
                col * (KEY_W + KEY_GAP_X);

            keyY[index] =
                KEYPAD_Y +
                row * (KEY_H + KEY_GAP_Y);
        }
    }
}

// ============================================================
// STYLE BOUTON
// ============================================================

static void drawButtonStyle(uint8_t index, bool pressed)
{
    if (index >= NUM_KEYS)
        return;

    const int16_t x = keyX[index];
    const int16_t y = keyY[index];

    uint16_t fillColor;
    uint16_t borderColor;
    uint16_t textColor;

    if (pressed)
    {
        fillColor   = UI_ACCENT;
        borderColor = UI_ACCENT;
        textColor   = TFT_BLACK;
    }
    else
    {
        fillColor   = UI_PANEL;
        borderColor = UI_ACCENT;
        textColor   = UI_TEXT;
    }

    // --------------------------------------------------------
    // Effacement de l'ancien bouton
    // --------------------------------------------------------

    tft.fillRoundRect(
        x,
        y,
        KEY_W,
        KEY_H,
        6,
        UI_BG
    );

    // --------------------------------------------------------
    // Fond
    // --------------------------------------------------------

    tft.fillRoundRect(
        x,
        y,
        KEY_W,
        KEY_H,
        6,
        fillColor
    );

    // --------------------------------------------------------
    // Bordure
    // --------------------------------------------------------

    tft.drawRoundRect(
        x,
        y,
        KEY_W,
        KEY_H,
        6,
        borderColor
    );

    // --------------------------------------------------------
    // Texte
    // --------------------------------------------------------

    tft.setTextFont(1);
    tft.setTextSize(KEY_TEXTSIZE);

    tft.setTextColor(
        textColor,
        fillColor
    );

    tft.setTextDatum(MC_DATUM);

    tft.drawString(
        keyLabel[index],
        x + KEY_W / 2,
        y + KEY_H / 2
    );

    tft.setTextDatum(TL_DATUM);
}

// ============================================================
// AFFICHAGE DU CLAVIER
// ============================================================

void drawKeypad()
{
    calculateKeyPositions();

    Serial.println("[UI] keypad layout:");

    for (uint8_t i = 0; i < NUM_KEYS; i++)
    {
        drawButtonStyle(i, false);

        Serial.printf(
            "[UI] btn=%u \"%s\" | x=%d y=%d w=%d h=%d\r\n",
            i,
            keyLabel[i],
            keyX[i],
            keyY[i],
            KEY_W,
            KEY_H
        );
    }
}

// ============================================================
// AFFICHAGE DE LA ZONE DE RETOUR
// ============================================================

void updateDisplay()
{
    // --------------------------------------------------------
    // Fond
    // --------------------------------------------------------

    tft.fillRoundRect(
        DISPLAY_X,
        DISPLAY_Y,
        DISPLAY_W,
        DISPLAY_H,
        5,
        UI_PANEL
    );

    // --------------------------------------------------------
    // Bordure
    // --------------------------------------------------------

    tft.drawRoundRect(
        DISPLAY_X,
        DISPLAY_Y,
        DISPLAY_W,
        DISPLAY_H,
        5,
        UI_ACCENT
    );
}

// ============================================================
// MISE À JOUR DU CLAVIER TACTILE
// ============================================================

void updateKeypad(
    uint16_t touchX,
    uint16_t touchY,
    bool pressed
)
{
    if (!pressed)
        return;

    for (uint8_t i = 0; i < NUM_KEYS; i++)
    {
        const int16_t x = keyX[i];
        const int16_t y = keyY[i];

        if (
            touchX >= x &&
            touchX < x + KEY_W &&
            touchY >= y &&
            touchY < y + KEY_H
        )
        {
            Serial.printf(
                "[KEY] %u \"%s\" | touch=%u,%u | rect=%d,%d,%d,%d\r\n",
                i,
                keyLabel[i],
                touchX,
                touchY,
                x,
                y,
                KEY_W,
                KEY_H
            );

            drawButtonStyle(i, true);

            // ------------------------------------------------
            // Affichage de la touche appuyée
            // ------------------------------------------------

            tft.fillRoundRect(
                DISPLAY_X + 2,
                DISPLAY_Y + 2,
                DISPLAY_W - 4,
                DISPLAY_H - 4,
                4,
                UI_PANEL
            );

            tft.setTextFont(1);
            tft.setTextSize(2);

            tft.setTextColor(
                UI_VALUE,
                UI_PANEL
            );

            tft.setTextDatum(MC_DATUM);

            tft.drawString(
                keyLabel[i],
                DISPLAY_X + DISPLAY_W / 2,
                DISPLAY_Y + DISPLAY_H / 2
            );

            tft.setTextDatum(TL_DATUM);

            delay(80);

            drawButtonStyle(i, false);

            return;
        }
    }
}

// ============================================================
// STATUS
// ============================================================

void status(const char *message)
{
    if (!message)
        return;

    // --------------------------------------------------------
    // Zone status
    // --------------------------------------------------------

    tft.fillRect(
        STATUS_X - STATUS_W / 2,
        STATUS_Y - STATUS_H / 2,
        STATUS_W,
        STATUS_H,
        UI_BG
    );

    // --------------------------------------------------------
    // Texte
    // --------------------------------------------------------

    tft.setTextFont(1);
    tft.setTextSize(1);

    tft.setTextColor(
        UI_TEXT_SECONDARY,
        UI_BG
    );

    tft.setTextDatum(MC_DATUM);

    tft.drawString(
        message,
        STATUS_X,
        STATUS_Y
    );

    tft.setTextDatum(TL_DATUM);

    Serial.printf(
        "[STATUS] %s\r\n",
        message
    );
}