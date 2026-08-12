// KEYPAD.ino

#include "settings.h"
#include "display.h"
#include "touch.h"
#include "keypad.h"
#include "calibration.h"

// ============================================================
// SETUP
// ============================================================

void setup()
{
    Serial.begin(115200);

    delay(200);

    Serial.println();
    Serial.println("==============================");
    Serial.println("  3x0c3t BO4RD KEYPAD v1.0");
    Serial.println("==============================");

    Serial.println("[TFT] Init");
    displayInit();
    Serial.println("[TFT] OK");

    Serial.println("[TOUCH] Init");
    touchInit();
    Serial.println("[TOUCH] OK");

    Serial.println("[KEYPAD] Init");
    keypadInit();
    Serial.println("[KEYPAD] OK");

    Serial.println("==============================");
    Serial.println("  SYSTEM READY");
    Serial.println("==============================");
}

// ============================================================
// LOOP
// ============================================================

void loop()
{
    keypadUpdate();

    delay(5);
}