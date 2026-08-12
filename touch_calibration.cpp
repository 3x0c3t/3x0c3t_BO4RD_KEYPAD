#include <FS.h>
#include <SPI.h>
#include <TFT_eSPI.h>

#include "config.h"
#include "touch_calibration.h"

extern TFT_eSPI tft;

void touch_calibrate()
{
  uint16_t calData[5];

  uint8_t calDataOK = 0;

  Serial.printf(
    "[TOUCH] +%lums | calibration init\n",
    millis()
  );

  if (!SPIFFS.begin())
  {
    Serial.printf(
      "[TOUCH] +%lums | SPIFFS FAIL | formatting\n",
      millis()
    );

    SPIFFS.format();

    if (SPIFFS.begin())
    {
      Serial.printf(
        "[TOUCH] +%lums | SPIFFS OK | after format\n",
        millis()
      );
    }
    else
    {
      Serial.printf(
        "[TOUCH] +%lums | SPIFFS FAIL | abort\n",
        millis()
      );
    }
  }
  else
  {
    Serial.printf(
      "[TOUCH] +%lums | SPIFFS OK\n",
      millis()
    );
  }

  if (SPIFFS.exists(CALIBRATION_FILE))
  {
    Serial.printf(
      "[TOUCH] +%lums | cal file FOUND | %s\n",
      millis(),
      CALIBRATION_FILE
    );

    if (REPEAT_CAL)
    {
      SPIFFS.remove(CALIBRATION_FILE);

      Serial.printf(
        "[TOUCH] +%lums | cal file REMOVED | recalibration\n",
        millis()
      );
    }
    else
    {
      File f = SPIFFS.open(
        CALIBRATION_FILE,
        "r"
      );

      if (f)
      {
        size_t bytes = f.readBytes(
          (char *)calData,
          14
        );

        if (bytes == 14)
        {
          calDataOK = 1;

          Serial.printf(
            "[TOUCH] +%lums | calibration LOADED | %u bytes | data=%u,%u,%u,%u,%u\n",
            millis(),
            bytes,
            calData[0],
            calData[1],
            calData[2],
            calData[3],
            calData[4]
          );
        }
        else
        {
          Serial.printf(
            "[TOUCH] +%lums | calibration INVALID | %u bytes\n",
            millis(),
            bytes
          );
        }

        f.close();
      }
      else
      {
        Serial.printf(
          "[TOUCH] +%lums | cal file OPEN FAIL\n",
          millis()
        );
      }
    }
  }
  else
  {
    Serial.printf(
      "[TOUCH] +%lums | cal file NOT FOUND | %s\n",
      millis(),
      CALIBRATION_FILE
    );
  }

  if (calDataOK && !REPEAT_CAL)
  {
    tft.setTouch(calData);

    Serial.printf(
      "[TOUCH] +%lums | calibration APPLIED\n",
      millis()
    );
  }
  else
  {
    Serial.printf(
      "[TOUCH] +%lums | calibration START\n",
      millis()
    );

    tft.fillScreen(TFT_BLACK);

    tft.setCursor(20, 0);

    tft.setTextFont(2);

    tft.setTextSize(1);

    tft.setTextColor(
      TFT_WHITE,
      TFT_BLACK
    );

    tft.println(
      "Touch corners as indicated"
    );

    tft.setTextFont(1);

    tft.println();

    if (REPEAT_CAL)
    {
      tft.setTextColor(
        TFT_RED,
        TFT_BLACK
      );

      tft.println(
        "Set REPEAT_CAL to false to stop this running again!"
      );
    }

    tft.calibrateTouch(
      calData,
      TFT_MAGENTA,
      TFT_BLACK,
      15
    );

    Serial.printf(
      "[TOUCH] +%lums | calibration DONE | data=%u,%u,%u,%u,%u\n",
      millis(),
      calData[0],
      calData[1],
      calData[2],
      calData[3],
      calData[4]
    );

    tft.setTextColor(
      TFT_GREEN,
      TFT_BLACK
    );

    tft.println(
      "Calibration complete!"
    );

    File f = SPIFFS.open(
      CALIBRATION_FILE,
      "w"
    );

    if (f)
    {
      size_t bytes = f.write(
        (const unsigned char *)calData,
        14
      );

      f.close();

      Serial.printf(
        "[TOUCH] +%lums | calibration SAVED | %u bytes\n",
        millis(),
        bytes
      );
    }
    else
    {
      Serial.printf(
        "[TOUCH] +%lums | calibration SAVE FAIL\n",
        millis()
      );
    }
  }

  Serial.printf(
    "[TOUCH] +%lums | READY\n",
    millis()
  );
}