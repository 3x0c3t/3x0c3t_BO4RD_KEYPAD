#include "display.h"
#include "settings.h"
#include "keypad.h"

void drawCalibrationScreen()
{
    tft.fillScreen(TFT_BLACK);

    tft.setTextDatum(MC_DATUM);

    tft.setTextFont(2);

    tft.setTextColor(
        TFT_GREEN,
        TFT_BLACK
    );

    tft.drawString(
        "CALIBRATION",
        SCREEN_WIDTH / 2,
        60
    );

    tft.setTextFont(1);

    tft.setTextColor(
        TFT_WHITE,
        TFT_BLACK
    );

    tft.drawString(
        "Touchez les points",
        SCREEN_WIDTH / 2,
        100
    );

    tft.drawString(
        "indiques a l'ecran",
        SCREEN_WIDTH / 2,
        120
    );
}

void drawCalibrationComplete()
{
    tft.fillScreen(TFT_BLACK);

    tft.drawRect(
        10,
        10,
        SCREEN_WIDTH - 20,
        SCREEN_HEIGHT - 20,
        TFT_GREEN
    );

    tft.setTextDatum(MC_DATUM);

    tft.setTextFont(2);

    tft.setTextColor(
        TFT_GREEN,
        TFT_BLACK
    );

    tft.drawString(
        "TOUCH OK",
        SCREEN_WIDTH / 2,
        110
    );

    tft.setTextFont(1);

    tft.setTextColor(
        TFT_WHITE,
        TFT_BLACK
    );

    tft.drawString(
        "Calibration terminee",
        SCREEN_WIDTH / 2,
        145
    );

    tft.setTextColor(
        TFT_CYAN,
        TFT_BLACK
    );

    tft.drawString(
        "KEYPAD",
        SCREEN_WIDTH / 2,
        180
    );

    delay(1000);
}

void drawInterface()
{
    tft.fillScreen(
        COLOR_BACKGROUND
    );

    drawHeader();

    drawValueDisplay();

    drawStatus("Pret");
}

void drawHeader()
{
    tft.fillRoundRect(
        HEADER_X,
        HEADER_Y,
        HEADER_W,
        HEADER_HEIGHT,
        5,
        COLOR_PANEL
    );

    tft.drawRoundRect(
        HEADER_X,
        HEADER_Y,
        HEADER_W,
        HEADER_HEIGHT,
        5,
        COLOR_BORDER
    );

    tft.setTextDatum(MC_DATUM);

    tft.setTextFont(2);

    tft.setTextColor(
        COLOR_ACCENT,
        COLOR_PANEL
    );

    tft.drawString(
        "3x0c3t KEYPAD",
        SCREEN_WIDTH / 2,
        HEADER_HEIGHT / 2
    );
}

void drawValueDisplay()
{
    tft.fillRoundRect(
        VALUE_X,
        VALUE_Y,
        VALUE_W,
        VALUE_HEIGHT,
        6,
        TFT_BLACK
    );

    tft.drawRoundRect(
        VALUE_X,
        VALUE_Y,
        VALUE_W,
        VALUE_HEIGHT,
        6,
        COLOR_BORDER
    );

    tft.setTextDatum(MR_DATUM);

    tft.setTextFont(4);

    tft.setTextColor(
        COLOR_NUMBER,
        TFT_BLACK
    );

    tft.drawString(
        getNumberBuffer(),
        VALUE_X + VALUE_W - 10,
        VALUE_Y + VALUE_HEIGHT / 2
    );
}

void updateDisplay()
{
    tft.fillRoundRect(
        VALUE_X + 1,
        VALUE_Y + 1,
        VALUE_W - 2,
        VALUE_HEIGHT - 2,
        5,
        TFT_BLACK
    );

    tft.setTextDatum(MR_DATUM);

    tft.setTextFont(4);

    tft.setTextColor(
        COLOR_NUMBER,
        TFT_BLACK
    );

    tft.drawString(
        getNumberBuffer(),
        VALUE_X + VALUE_W - 10,
        VALUE_Y + VALUE_HEIGHT / 2
    );
}

void drawStatus(const char *msg)
{
    tft.fillRect(
        0,
        298,
        SCREEN_WIDTH,
        22,
        TFT_BLACK
    );

    tft.setTextDatum(MC_DATUM);

    tft.setTextFont(1);

    tft.setTextColor(
        COLOR_ACCENT,
        TFT_BLACK
    );

    tft.drawString(
        msg,
        SCREEN_WIDTH / 2,
        309
    );
}