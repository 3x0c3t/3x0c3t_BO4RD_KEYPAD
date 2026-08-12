#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>

#include "config.h"
#include "keypad.h"
#include "touch_calibration.h"

TFT_eSPI tft = TFT_eSPI();

unsigned long bootTime = 0;

void setup()
{
  bootTime = millis();

  Serial.begin(115200);
  delay(100);

  Serial.println();
  Serial.println("[SYS] BO4RD KEYPAD v1.0");

  tft.init();
  tft.setRotation(TFT_ROTATION);

  Serial.printf(
    "[TFT] +%lums | init OK | rot=%u | size=%ux%u\n",
    millis(),
    TFT_ROTATION,
    tft.width(),
    tft.height()
  );

  touch_calibrate();

  tft.fillScreen(COLOR_BACKGROUND);

  tft.setFreeFont(&FreeMonoBold9pt7b);
  tft.setTextColor(COLOR_ACCENT, COLOR_BACKGROUND);
  tft.setTextDatum(TL_DATUM);

  tft.drawString(
    "3x0c3t BO4RD",
    HEADER_X,
    HEADER_Y
  );

  tft.setFreeFont(&FreeMonoBold9pt7b);
  tft.setTextColor(COLOR_TEXT_DIM, COLOR_BACKGROUND);
  tft.setTextDatum(TR_DATUM);

  tft.drawString(
    "v1.0",
    HEADER_X + HEADER_W,
    HEADER_Y
  );

  tft.drawFastHLine(
    HEADER_X,
    HEADER_Y + HEADER_H,
    HEADER_W,
    COLOR_ACCENT
  );

  tft.setTextDatum(TL_DATUM);
  tft.setTextColor(COLOR_TEXT_DIM, COLOR_BACKGROUND);

  tft.drawString(
    "KEYPAD",
    HEADER_X,
    HEADER_Y + 17
  );

  Serial.printf(
    "[UI] +%lums | header OK\n",
    millis()
  );

  updateDisplay();

  tft.drawFastHLine(
    DISPLAY_X,
    DISPLAY_Y + DISPLAY_H + 3,
    DISPLAY_W,
    TFT_DARKGREY
  );

  drawKeypad();

  status("READY");

  Serial.printf(
    "[UI] +%lums | display OK\n",
    millis()
  );

  Serial.printf(
    "[SYS] READY | boot=%lums\n",
    millis()
  );
}

void loop()
{
  uint16_t t_x = 0;
  uint16_t t_y = 0;

  bool pressed = tft.getTouch(&t_x, &t_y);

  if (pressed)
  {
    Serial.printf(
      "[TOUCH] x=%u y=%u\n",
      t_x,
      t_y
    );
  }

  updateKeypad(
    t_x,
    t_y,
    pressed
  );

  delay(10);
}