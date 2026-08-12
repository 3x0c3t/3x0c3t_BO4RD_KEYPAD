#include "touch.h"

#include <Arduino.h>
#include <TFT_eSPI.h>

#include "calibration.h"

extern TFT_eSPI tft;

void touchInit()
{
    calibrationInit();
}

bool touchRead(
    uint16_t &x,
    uint16_t &y
)
{
    if (!calibrationIsValid())
    {
        return false;
    }

    return tft.getTouch(
        &x,
        &y
    );
}