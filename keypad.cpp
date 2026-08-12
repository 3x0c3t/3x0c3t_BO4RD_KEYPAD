#include "keypad.h"

#include <Arduino.h>
#include <TFT_eSPI.h>

#include "settings.h"
#include "display.h"

extern TFT_eSPI tft;

// ============================================================
// Labels
// ============================================================

char keyLabel[KEY_COUNT][8] =
{
    "NEW",
    "DEL",
    "SEND",

    "1",
    "2",
    "3",

    "4",
    "5",
    "6",

    "7",
    "8",
    "9",

    ".",
    "0",
    "#"
};

// ============================================================
// Couleurs
// ============================================================

const uint16_t keyColor[KEY_COUNT] =
{
    TFT_RED,
    TFT_DARKGREY,
    TFT_DARKGREEN,

    TFT_BLUE,
    TFT_BLUE,
    TFT_BLUE,

    TFT_BLUE,
    TFT_BLUE,
    TFT_BLUE,

    TFT_BLUE,
    TFT_BLUE,
    TFT_BLUE,

    TFT_BLUE,
    TFT_BLUE,
    TFT_BLUE
};

// ============================================================
// Boutons
// ============================================================

TFT_eSPI_Button key[KEY_COUNT];

// ============================================================
// Buffer
// ============================================================

char numberBuffer[NUM_LEN + 1] = "";

uint8_t numberIndex = 0;

// ============================================================
// Acces buffer
// ============================================================

const char *getNumberBuffer()
{
    return numberBuffer;
}

// ============================================================
// Initialisation
// ============================================================

void keypadInit()
{
    drawInterface();

    drawKeypad();
}

// ============================================================
// Dessin clavier
// ============================================================

void drawKeypad()
{
    for (
        uint8_t row = 0;
        row < 5;
        row++
    )
    {
        for (
            uint8_t col = 0;
            col < 3;
            col++
        )
        {
            uint8_t b =
                col + row * 3;

            uint16_t x =
                KEY_START_X +
                col *
                (
                    KEY_W +
                    KEY_SPACING_X
                );

            uint16_t y =
                KEY_START_Y +
                row *
                (
                    KEY_H +
                    KEY_SPACING_Y
                );

            key[b].initButton(
                &tft,

                x + KEY_W / 2,
                y + KEY_H / 2,

                KEY_W,
                KEY_H,

                TFT_WHITE,
                keyColor[b],
                TFT_WHITE,

                keyLabel[b],

                1
            );

            key[b].drawButton();
        }
    }
}

// ============================================================
// Boucle
// ============================================================

void keypadLoop()
{
    uint16_t x = 0;
    uint16_t y = 0;

    bool pressed =
        tft.getTouch(
            &x,
            &y
        );

    // --------------------------------------------------------
    // Etat des boutons
    // --------------------------------------------------------

    for (
        uint8_t b = 0;
        b < KEY_COUNT;
        b++
    )
    {
        if (
            pressed &&
            key[b].contains(
                x,
                y
            )
        )
        {
            key[b].press(true);
        }
        else
        {
            key[b].press(false);
        }
    }

    // --------------------------------------------------------
    // Evenements
    // --------------------------------------------------------

    for (
        uint8_t b = 0;
        b < KEY_COUNT;
        b++
    )
    {
        if (
            key[b].justReleased()
        )
        {
            key[b].drawButton();
        }

        if (
            key[b].justPressed()
        )
        {
            key[b].drawButton(true);

            Serial.print(
                "[TOUCH] X="
            );

            Serial.print(x);

            Serial.print(
                " Y="
            );

            Serial.print(y);

            Serial.print(
                " -> "
            );

            Serial.println(
                keyLabel[b]
            );

            handleKey(b);

            delay(120);
        }
    }
}

// ============================================================
// Traitement
// ============================================================

void handleKey(
    uint8_t index
)
{
    // --------------------------------------------------------
    // NEW
    // --------------------------------------------------------

    if (index == 0)
    {
        numberIndex = 0;

        numberBuffer[0] =
            '\0';

        updateDisplay();

        drawStatus(
            "Nouveau"
        );

        return;
    }

    // --------------------------------------------------------
    // DEL
    // --------------------------------------------------------

    if (index == 1)
    {
        if (
            numberIndex > 0
        )
        {
            numberIndex--;

            numberBuffer[numberIndex] =
                '\0';
        }

        updateDisplay();

        drawStatus(
            "Suppression"
        );

        return;
    }

    // --------------------------------------------------------
    // SEND
    // --------------------------------------------------------

    if (index == 2)
    {
        Serial.print(
            "[KEYPAD] SEND -> "
        );

        Serial.println(
            numberBuffer
        );

        drawStatus(
            "Envoye"
        );

        return;
    }

    // --------------------------------------------------------
    // Chiffres
    // --------------------------------------------------------

    if (
        index >= 3
    )
    {
        if (
            numberIndex <
            NUM_LEN
        )
        {
            numberBuffer[numberIndex] =
                keyLabel[index][0];

            numberIndex++;

            numberBuffer[numberIndex] =
                '\0';
        }

        updateDisplay();

        drawStatus(
            "Entree"
        );
    }
}