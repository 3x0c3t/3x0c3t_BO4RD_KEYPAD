#include "keypad.h"
#include "display.h"
#include "touch.h"
#include "settings.h"

String keypadValue = "";

unsigned long lastTouch = 0;

#define TOUCH_DEBOUNCE 180

// ============================================================
// DECLARATIONS
// ============================================================

static void processKey(int row, int col);

// ============================================================
// INIT
// ============================================================

void keypadInit()
{
    keypadValue = "";

    displayDrawResult(keypadValue);
}

// ============================================================
// CLEAR
// ============================================================

void keypadClear()
{
    keypadValue = "";

    displayDrawResult(keypadValue);
}

// ============================================================
// VALEUR
// ============================================================

String keypadGetValue()
{
    return keypadValue;
}

// ============================================================
// DETECTION TOUCHE
// ============================================================

void keypadUpdate()
{
    if (millis() - lastTouch < TOUCH_DEBOUNCE)
        return;

    int16_t x;
    int16_t y;

    if (!touchRead(x, y))
        return;

    lastTouch = millis();

    // --------------------------------------------------------
    // Recherche du bouton
    // --------------------------------------------------------

    for (int row = 0; row < KEY_ROWS; row++)
    {
        for (int col = 0; col < KEY_COLS; col++)
        {
            int keyX =
                KEY_START_X +
                col * (KEY_W + KEY_GAP_X);

            int keyY =
                KEY_START_Y +
                row * (KEY_H + KEY_GAP_Y);

            if (
                x >= keyX &&
                x < keyX + KEY_W &&
                y >= keyY &&
                y < keyY + KEY_H
            )
            {
                processKey(row, col);
                return;
            }
        }
    }
}

// ============================================================
// TRAITEMENT TOUCHE
// ============================================================

static void processKey(int row, int col)
{
    const char *keys[KEY_ROWS][KEY_COLS] =
    {
        { "1", "2", "3" },
        { "4", "5", "6" },
        { "7", "8", "9" },
        { "*", "0", "#" },
        { "C", "OK", "<" }
    };

    String key = keys[row][col];

    // --------------------------------------------------------
    // CLEAR
    // --------------------------------------------------------

    if (key == "C")
    {
        keypadClear();

        Serial.println("[KEYPAD] CLEAR");

        return;
    }

    // --------------------------------------------------------
    // RETOUR ARRIERE
    // --------------------------------------------------------

    if (key == "<")
    {
        if (keypadValue.length() > 0)
        {
            keypadValue.remove(
                keypadValue.length() - 1
            );

            displayDrawResult(keypadValue);
        }

        Serial.println("[KEYPAD] BACK");

        return;
    }

    // --------------------------------------------------------
    // VALIDATION
    // --------------------------------------------------------

    if (key == "OK")
    {
        Serial.print("[KEYPAD] OK : ");
        Serial.println(keypadValue);

        return;
    }

    // --------------------------------------------------------
    // CARACTERE
    // --------------------------------------------------------

    keypadValue += key;

    displayDrawResult(keypadValue);

    Serial.print("[KEYPAD] ");
    Serial.println(key);
}