#include <Arduino.h>
#include <TFT_eSPI.h>

#include "config.h"
#include "keypad.h"
#include "touch_calibration.h"


// ============================================================
// TFT
// ============================================================

TFT_eSPI tft = TFT_eSPI();


// ============================================================
// SETUP
// ============================================================

void setup()
{
    Serial.begin(115200);

    delay(100);

    Serial.println();
    Serial.println("[SYS] BO4RD KEYPAD v1.0");

    unsigned long startTime = millis();

    // --------------------------------------------------------
    // TFT
    // --------------------------------------------------------

    tft.init();
    tft.setRotation(TFT_ROTATION);

    Serial.printf(
        "[TFT] +%lums | init OK | rot=%d | size=%dx%d\n",
        millis() - startTime,
        TFT_ROTATION,
        tft.width(),
        tft.height()
    );

    // --------------------------------------------------------
    // TOUCH
    // --------------------------------------------------------

    touch_calibrate();

    // --------------------------------------------------------
    // INTERFACE
    // --------------------------------------------------------

    tft.fillScreen(COLOR_BACKGROUND);

    Serial.printf(
        "[UI] +%lums | background OK\n",
        millis() - startTime
    );

    // --------------------------------------------------------
    // HEADER
    // --------------------------------------------------------

    tft.fillRect(
        HEADER_X,
        HEADER_Y,
        HEADER_W,
        HEADER_H,
        COLOR_BACKGROUND
    );

    tft.setTextDatum(MC_DATUM);
    tft.setTextFont(2);
    tft.setTextColor(
        COLOR_ACCENT,
        COLOR_BACKGROUND
    );

    tft.drawString(
        "KEYPAD",
        SCREEN_WIDTH / 2,
        HEADER_Y + HEADER_H / 2,
        2
    );

    tft.drawFastHLine(
        0,
        HEADER_LINE_Y,
        SCREEN_WIDTH,
        COLOR_PANEL
    );

    Serial.printf(
        "[UI] +%lums | header OK\n",
        millis() - startTime
    );

    // --------------------------------------------------------
    // ZONE AFFICHAGE
    // --------------------------------------------------------

    tft.fillRoundRect(
        DISPLAY_X,
        DISPLAY_Y,
        DISPLAY_W,
        DISPLAY_H,
        5,
        COLOR_PANEL
    );

    tft.drawRoundRect(
        DISPLAY_X,
        DISPLAY_Y,
        DISPLAY_W,
        DISPLAY_H,
        5,
        COLOR_ACCENT
    );

    Serial.printf(
        "[UI] +%lums | display OK | x=%d y=%d w=%d h=%d\n",
        millis() - startTime,
        DISPLAY_X,
        DISPLAY_Y,
        DISPLAY_W,
        DISPLAY_H
    );

    // --------------------------------------------------------
    // KEYPAD
    // --------------------------------------------------------

    drawKeypad();

    Serial.printf(
        "[UI] +%lums | keypad OK\n",
        millis() - startTime
    );

    Serial.printf(
        "[SYS] READY | total=%lums\n",
        millis() - startTime
    );
}


// ============================================================
// LOOP
// ============================================================

void loop()
{
    uint16_t t_x = 0;
    uint16_t t_y = 0;

    bool pressed = tft.getTouch(
        &t_x,
        &t_y
    );

    updateKeypad(
        t_x,
        t_y,
        pressed
    );

    delay(10);
}