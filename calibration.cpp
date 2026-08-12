#include "calibration.h"

#include <Arduino.h>
#include <FS.h>
#include <TFT_eSPI.h>

#include "settings.h"
#include "display.h"

extern TFT_eSPI tft;

static bool calibrationValid = false;

void calibrationInit()
{
    uint16_t calData[5];

    calibrationValid = false;

    Serial.println(
        "[CAL] Initialisation..."
    );

    // --------------------------------------------------------
    // SPIFFS
    // --------------------------------------------------------

    if (!SPIFFS.begin())
    {
        Serial.println(
            "[CAL] SPIFFS absent"
        );

        Serial.println(
            "[CAL] Formatage..."
        );

        SPIFFS.format();

        if (!SPIFFS.begin())
        {
            Serial.println(
                "[CAL] ERREUR SPIFFS"
            );

            return;
        }
    }

    // --------------------------------------------------------
    // Calibration existante
    // --------------------------------------------------------

    if (
        SPIFFS.exists(
            CALIBRATION_FILE
        )
    )
    {
        Serial.println(
            "[CAL] Fichier trouve"
        );

        if (!REPEAT_CAL)
        {
            fs::File f =
                SPIFFS.open(
                    CALIBRATION_FILE,
                    "r"
                );

            if (f)
            {
                size_t size =
                    f.readBytes(
                        (char *)calData,
                        14
                    );

                f.close();

                if (size == 14)
                {
                    tft.setTouch(
                        calData
                    );

                    calibrationValid = true;

                    Serial.println(
                        "[CAL] Calibration chargee"
                    );

                    return;
                }
            }

            Serial.println(
                "[CAL] Fichier invalide"
            );
        }
        else
        {
            Serial.println(
                "[CAL] REPEAT_CAL actif"
            );

            SPIFFS.remove(
                CALIBRATION_FILE
            );
        }
    }

    // --------------------------------------------------------
    // Nouvelle calibration
    // --------------------------------------------------------

    Serial.println();

    Serial.println(
        "=============================="
    );

    Serial.println(
        "       CALIBRATION TOUCH"
    );

    Serial.println(
        "=============================="
    );

    drawCalibrationScreen();

    delay(500);

    Serial.println(
        "[CAL] Calibration en cours..."
    );

    tft.calibrateTouch(
        calData,
        TFT_MAGENTA,
        TFT_BLACK,
        15
    );

    Serial.println(
        "[CAL] Calibration terminee"
    );

    // --------------------------------------------------------
    // Activation
    // --------------------------------------------------------

    tft.setTouch(
        calData
    );

    // --------------------------------------------------------
    // Sauvegarde
    // --------------------------------------------------------

    fs::File f =
        SPIFFS.open(
            CALIBRATION_FILE,
            "w"
        );

    if (f)
    {
        f.write(
            (const unsigned char *)calData,
            14
        );

        f.close();

        Serial.println(
            "[CAL] Calibration sauvegardee"
        );

        calibrationValid = true;
    }
    else
    {
        Serial.println(
            "[CAL] ERREUR sauvegarde"
        );
    }

    // --------------------------------------------------------
    // Confirmation
    // --------------------------------------------------------

    drawCalibrationComplete();

    delay(800);
}

bool calibrationIsValid()
{
    return calibrationValid;
}