#include <Arduino.h>
#include <TFT_eSPI.h>

#include "settings.h"
#include "display.h"
#include "touch.h"
#include "keypad.h"

TFT_eSPI tft = TFT_eSPI();

void setup()
{
    Serial.begin(
        SERIAL_BAUD
    );

    delay(300);

    Serial.println();

    Serial.println(
        "=============================="
    );

    Serial.println(
        "       3x0c3t BO4RD"
    );

    Serial.println(
        "          KEYPAD"
    );

    Serial.println(
        "=============================="
    );

    // --------------------------------------------------------
    // TFT
    // --------------------------------------------------------

    Serial.println(
        "[TFT] Initialisation..."
    );

    tft.init();

    tft.setRotation(
        TFT_ROTATION
    );

    tft.fillScreen(
        COLOR_BACKGROUND
    );

    Serial.println(
        "[TFT] OK"
    );

    // --------------------------------------------------------
    // TOUCH
    // --------------------------------------------------------

    touchInit();

    // --------------------------------------------------------
    // KEYPAD
    // --------------------------------------------------------

    keypadInit();

    Serial.println();

    Serial.println(
        "=============================="
    );

    Serial.println(
        "       KEYPAD READY"
    );

    Serial.println(
        "=============================="
    );

    Serial.println(
        "[TOUCH] Touchez un bouton"
    );

    Serial.println();
}

void loop()
{
    keypadLoop();

    delay(10);
}