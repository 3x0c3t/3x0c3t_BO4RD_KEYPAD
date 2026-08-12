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

  if (!SPIFFS.begin())
  {
    Serial.println("formatting file system");

    SPIFFS.format();

    SPIFFS.begin();
  }

  if (SPIFFS.exists(CALIBRATION_FILE))
  {
    if (REPEAT_CAL)
    {
      SPIFFS.remove(CALIBRATION_FILE);
    }
    else
    {
      File f = SPIFFS.open(CALIBRATION_FILE, "r");

      if (f)
      {
        if (f.readBytes((char *)calData, 14) == 14)
        {
          calDataOK = 1;
        }

        f.close();
      }
    }
  }

  if (calDataOK && !REPEAT_CAL)
  {
    tft.setTouch(calData);
  }
  else
  {
    tft.fillScreen(TFT_BLACK);

    tft.setCursor(20, 0);

    tft.setTextFont(2);

    tft.setTextSize(1);

    tft.setTextColor(TFT_WHITE, TFT_BLACK);

    tft.println("Touch corners as indicated");

    tft.setTextFont(1);

    tft.println();

    if (REPEAT_CAL)
    {
      tft.setTextColor(TFT_RED, TFT_BLACK);

      tft.println("Set REPEAT_CAL to false to stop this running again!");
    }

    tft.calibrateTouch(
      calData,
      TFT_MAGENTA,
      TFT_BLACK,
      15
    );

    tft.setTextColor(TFT_GREEN, TFT_BLACK);

    tft.println("Calibration complete!");

    File f = SPIFFS.open(CALIBRATION_FILE, "w");

    if (f)
    {
      f.write(
        (const unsigned char *)calData,
        14
      );

      f.close();
    }
  }
}