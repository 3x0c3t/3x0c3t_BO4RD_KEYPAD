#include "config.h"
#include "keypad.h"
#include "touch_calibration.h"

TFT_eSPI tft = TFT_eSPI();

void setup()
{
  Serial.begin(115200);

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

  tft.fillScreen(COLOR_BACKGROUND);

  Serial.printf(
    "[UI] +%lums | background OK\n",
    millis()
  );

  tft.fillRect(
    DISP_X,
    DISP_Y,
    DISP_W,
    DISP_H,
    COLOR_BACKGROUND
  );

  tft.drawRect(
    DISP_X,
    DISP_Y,
    DISP_W,
    DISP_H,
    COLOR_ACCENT
  );

  Serial.printf(
    "[UI] +%lums | display OK\n",
    millis()
  );

  drawKeypad();
}

void loop()
{
  uint16_t t_x = 0;
  uint16_t t_y = 0;

  bool pressed = tft.getTouch(&t_x, &t_y);

  if (pressed) {

    Serial.printf(
      "[TOUCH] +%lums | x=%u y=%u\n",
      millis(),
      t_x,
      t_y
    );
  }

  updateKeypad(t_x, t_y, pressed);
}