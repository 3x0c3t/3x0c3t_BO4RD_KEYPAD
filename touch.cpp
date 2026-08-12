#include "touch.h"
#include "settings.h"

#include <SPI.h>
#include <XPT2046_Touchscreen.h>

// ============================================================
// TOUCH XPT2046
// ============================================================

XPT2046_Touchscreen touch(
    TOUCH_CS,
    TOUCH_IRQ
);

// ============================================================
// CALIBRATION
// ============================================================

#define TOUCH_MIN_X  200
#define TOUCH_MAX_X 3900

#define TOUCH_MIN_Y  200
#define TOUCH_MAX_Y 3900

// ============================================================
// INITIALISATION
// ============================================================

void touchInit()
{
    touch.begin();

    touch.setRotation(TFT_ROTATION);

    Serial.println("[TOUCH] XPT2046 OK");
}

// ============================================================
// TOUCH DETECTEE
// ============================================================

bool touchAvailable()
{
    return touch.touched();
}

// ============================================================
// LECTURE TOUCH
// ============================================================

bool touchRead(
    int16_t &x,
    int16_t &y
)
{
    if (!touch.touched())
    {
        return false;
    }

    TS_Point p = touch.getPoint();

    // --------------------------------------------------------
    // RAW -> ECRAN
    // --------------------------------------------------------

    x = map(
        p.x,
        TOUCH_MIN_X,
        TOUCH_MAX_X,
        0,
        TFT_WIDTH - 1
    );

    y = map(
        p.y,
        TOUCH_MIN_Y,
        TOUCH_MAX_Y,
        0,
        TFT_HEIGHT - 1
    );

    // --------------------------------------------------------
    // LIMITES
    // --------------------------------------------------------

    x = constrain(
        x,
        0,
        TFT_WIDTH - 1
    );

    y = constrain(
        y,
        0,
        TFT_HEIGHT - 1
    );

    return true;
}