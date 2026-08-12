#include "touch_calibration.h"
#include "config.h"

#include <FS.h>

extern TFT_eSPI tft;

void touch_calibrate()
{
  uint16_t calData[5];
  uint8_t calDataOK = 0;

  Serial.println("[TOUCH] calibration init");

  if (!SPIFFS.begin())
  {
    Serial.println("[TOUCH] SPIFFS FAIL | formatting");

    SPIFFS.format();

    if (!SPIFFS.begin())
    {
      Serial.println("[TOUCH] SPIFFS ERROR");
      return;
    }
  }

  Serial.println("[TOUCH] SPIFFS OK");

  if (SPIFFS.exists(CALIBRATION_FILE))
  {
    Serial.printf(
      "[TOUCH] cal file FOUND | %s\n",
      CALIBRATION_FILE
    );

    if (REPEAT_CAL)
    {
      SPIFFS.remove(CALIBRATION_FILE);

      Serial.println("[TOUCH] calibration file DELETED");
    }
    else
    {
      fs::File f = SPIFFS.open(
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
            "[TOUCH] calibration LOADED | 14 bytes | data=%u,%u,%u,%u,%u\n",
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
            "[TOUCH] calibration INVALID | bytes=%u\n",
            bytes
          );
        }

        f.close();
      }
      else
      {
        Serial.println("[TOUCH] calibration OPEN FAIL");
      }
    }
  }
  else
  {
    Serial.println("[TOUCH] cal file NOT FOUND");
  }

  if (calDataOK && !REPEAT_CAL)
  {
    tft.setTouch(calData);

    Serial.println("[TOUCH] calibration APPLIED");
    Serial.println("[TOUCH] READY");

    return;
  }

  Serial.println("[TOUCH] calibration REQUIRED");

  tft.fillScreen(TFT_BLACK);

  tft.setCursor(20, 20);
  tft.setTextFont(2);
  tft.setTextSize(1);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);

  tft.println("Touch corners");

  tft.setTextFont(1);
  tft.println();

  if (REPEAT_CAL)
  {
    tft.setTextColor(TFT_RED, TFT_BLACK);
    tft.println("REPEAT_CAL = true");
  }

  tft.calibrateTouch(
    calData,
    TFT_MAGENTA,
    TFT_BLACK,
    15
  );

  tft.setTextColor(
    TFT_GREEN,
    TFT_BLACK
  );

  tft.println("Calibration complete!");

  fs::File f = SPIFFS.open(
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

    Serial.printf(
      "[TOUCH] calibration SAVED | data=%u,%u,%u,%u,%u\n",
      calData[0],
      calData[1],
      calData[2],
      calData[3],
      calData[4]
    );
  }
  else
  {
    Serial.println("[TOUCH] calibration SAVE FAIL");
  }

  tft.setTouch(calData);

  Serial.println("[TOUCH] READY");
}