#include <FS.h>
#include <SPI.h>
#include <TFT_eSPI.h>

#include "config.h"
#include "keypad.h"
#include "touch_calibration.h"

TFT_eSPI tft = TFT_eSPI();

char numberBuffer[NUM_LEN + 1] = "";
uint8_t numberIndex = 0;

void setup()
{
  Serial.begin(115200);

  delay(100);

  Serial.println();
  Serial.println("[SYS] BO4RD KEYPAD v1.0");

  tft.init();

  tft.setRotation(TFT_ROTATION);

  Serial.printf(
    "[TFT] +%lums | init OK | rot=%d | size=%dx%d\n",
    millis(),
    TFT_ROTATION,
    tft.width(),
    tft.height()
  );

  touch_calibrate();

  tft.fillScreen(TFT_BLACK);

  Serial.printf(
    "[UI] +%lums | background OK\n",
    millis()
  );

  tft.fillRect(
    0,
    0,
    SCREEN_WIDTH,
    SCREEN_HEIGHT,
    TFT_DARKGREY
  );

  tft.fillRect(
    DISP_X,
    DISP_Y,
    DISP_W,
    DISP_H,
    TFT_BLACK
  );

  tft.drawRect(
    DISP_X,
    DISP_Y,
    DISP_W,
    DISP_H,
    TFT_WHITE
  );

  Serial.printf(
    "[UI] +%lums | display OK\n",
    millis()
  );

  drawKeypad();

  Serial.printf(
    "[UI] +%lums | keypad OK | buttons=15\n",
    millis()
  );

  Serial.printf(
    "[SYS] +%lums | READY\n",
    millis()
  );
}

void loop()
{
  uint16_t t_x = 0;
  uint16_t t_y = 0;
  uint16_t raw_x = 0;
  uint16_t raw_y = 0;
  uint16_t touchZ = 0;

  bool pressed = tft.getTouch(&t_x, &t_y);

  if (pressed)
  {
    tft.getTouchRaw(&raw_x, &raw_y);

    touchZ = tft.getTouchRawZ();
  }

  for (uint8_t b = 0; b < 15; b++)
  {
    if (pressed && key[b].contains(t_x, t_y))
    {
      key[b].press(true);
    }
    else
    {
      key[b].press(false);
    }
  }

  for (uint8_t b = 0; b < 15; b++)
  {
    if (b < 3)
    {
      tft.setFreeFont(LABEL1_FONT);
    }
    else
    {
      tft.setFreeFont(LABEL2_FONT);
    }

    if (key[b].justReleased())
    {
      key[b].drawButton();

      Serial.printf(
        "[TOUCH] +%lums | raw=%u,%u | xy=%u,%u | z=%u | btn=%u \"%s\" | RELEASE\n",
        millis(),
        raw_x,
        raw_y,
        t_x,
        t_y,
        touchZ,
        b,
        keyLabel[b]
      );
    }

    if (key[b].justPressed())
    {
      key[b].drawButton(true);

      Serial.printf(
        "[TOUCH] +%lums | raw=%u,%u | xy=%u,%u | z=%u | btn=%u \"%s\" | PRESS\n",
        millis(),
        raw_x,
        raw_y,
        touchZ,
        b,
        keyLabel[b]
      );

      if (b >= 3)
      {
        if (numberIndex < NUM_LEN)
        {
          numberBuffer[numberIndex] = keyLabel[b][0];

          numberIndex++;

          numberBuffer[numberIndex] = 0;
        }

        status("");

        Serial.printf(
          "[KEY]   +%lums | \"%s\" | buffer=\"%s\"\n",
          millis(),
          keyLabel[b],
          numberBuffer
        );
      }

      if (b == 1)
      {
        numberBuffer[numberIndex] = 0;

        if (numberIndex > 0)
        {
          numberIndex--;

          numberBuffer[numberIndex] = 0;
        }

        status("");

        Serial.printf(
          "[KEY]   +%lums | DEL | buffer=\"%s\"\n",
          millis(),
          numberBuffer
        );
      }

      if (b == 2)
      {
        status("Sent value to serial port");

        Serial.printf(
          "[KEY]   +%lums | SEND | buffer=\"%s\"\n",
          millis(),
          numberBuffer
        );

        Serial.println(numberBuffer);
      }

      if (b == 0)
      {
        status("Value cleared");

        numberIndex = 0;

        numberBuffer[numberIndex] = 0;

        Serial.printf(
          "[KEY]   +%lums | NEW | buffer=\"\"\n",
          millis()
        );
      }

      tft.setTextDatum(TL_DATUM);

      tft.setFreeFont(&FreeSans18pt7b);

      tft.setTextColor(DISP_TCOLOR);

      int xwidth = tft.drawString(
        numberBuffer,
        DISP_X + 4,
        DISP_Y + 12
      );

      if (xwidth < DISP_W - 5)
      {
        tft.fillRect(
          DISP_X + 4 + xwidth,
          DISP_Y + 1,
          DISP_W - xwidth - 5,
          DISP_H - 2,
          TFT_BLACK
        );
      }

      delay(10);
    }
  }
}