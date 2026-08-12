// calibration.cpp
#include "calibration.h"
#include "display.h"
#include "touch.h"
#include "settings.h"

// ============================================================
// CALIBRATION
// ============================================================

void calibrationInit()
{
    Serial.println("[CALIBRATION] Init");
}

// ============================================================
// CALIBRATION RUN
// ============================================================

void calibrationRun()
{
    Serial.println("[CALIBRATION] Run");

    // Calibration matérielle conservée séparément.
    // Les valeurs finales sont définies dans touch.cpp.
}