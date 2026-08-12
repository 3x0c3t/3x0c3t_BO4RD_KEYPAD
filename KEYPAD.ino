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
  Serial.begin(9600);

  tft.init();

  tft.setRotation(TFT_ROTATION);

  touch_calibrate();

  tft.fillScreen(TFT_BLACK);

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

  drawKeypad();
}

void loop()
{
  uint16_t t_x = 0;
  uint16_t t_y = 0;

  bool pressed = tft.getTouch(&t_x, &t_y);

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
    }

    if (key[b].justPressed())
    {
      key[b].drawButton(true);

      if (b >= 3)
      {
        if (numberIndex < NUM_LEN)
        {
          numberBuffer[numberIndex] = keyLabel[b][0];

          numberIndex++;

          numberBuffer[numberIndex] = 0;
        }

        status("");
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
      }

      if (b == 2)
      {
        status("Sent value to serial port");

        Serial.println(numberBuffer);
      }

      if (b == 0)
      {
        status("Value cleared");

        numberIndex = 0;

        numberBuffer[numberIndex] = 0;
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