#include "keypad.h"
#include "config.h"

char keyLabel[15][5] = {
  "New", "Del", "Send",
  "1", "2", "3",
  "4", "5", "6",
  "7", "8", "9",
  ".", "0", "#"
};

uint16_t keyColor[15] = {
  COLOR_OK,
  COLOR_WARNING,
  COLOR_ACCENT,
  COLOR_ACTION,
  COLOR_ACTION,
  COLOR_ACTION,
  COLOR_ACTION,
  COLOR_ACTION,
  COLOR_ACTION,
  COLOR_ACTION,
  COLOR_ACTION,
  COLOR_ACTION,
  COLOR_ACTION,
  COLOR_ACTION,
  COLOR_ACTION
};

TFT_eSPI_Button key[15];

char numberBuffer[NUM_LEN + 1] = "";
uint8_t numberIndex = 0;

void drawKeypad()
{
  Serial.println("[UI] keypad draw");

  for (uint8_t row = 0; row < 5; row++) {
    for (uint8_t col = 0; col < 3; col++) {

      uint8_t b = col + row * 3;

      if (b < 3) {
        tft.setFreeFont(LABEL1_FONT);
      } else {
        tft.setFreeFont(LABEL2_FONT);
      }

      key[b].initButton(
        &tft,
        KEY_X + col * (KEY_W + KEY_SPACING_X),
        KEY_Y + row * (KEY_H + KEY_SPACING_Y),
        KEY_W,
        KEY_H,
        COLOR_TEXT,
        keyColor[b],
        COLOR_TEXT,
        keyLabel[b],
        KEY_TEXTSIZE
      );

      key[b].drawButton();

      Serial.printf(
        "[UI]     +%lums | btn=%u \"%s\" | x=%d y=%d w=%d h=%d\n",
        millis(),
        b,
        keyLabel[b],
        KEY_X + col * (KEY_W + KEY_SPACING_X),
        KEY_Y + row * (KEY_H + KEY_SPACING_Y),
        KEY_W,
        KEY_H
      );
    }
  }

  Serial.println("[UI] keypad OK");
}

void updateDisplay()
{
  tft.setTextDatum(TL_DATUM);
  tft.setFreeFont(&FreeSans18pt7b);
  tft.setTextColor(COLOR_DATA, COLOR_BACKGROUND);

  int xwidth = tft.drawString(
    numberBuffer,
    DISP_X + 4,
    DISP_Y + 12
  );

  int clearWidth = DISP_W - xwidth - 5;

  if (clearWidth > 0) {
    tft.fillRect(
      DISP_X + 4 + xwidth,
      DISP_Y + 1,
      clearWidth,
      DISP_H - 2,
      COLOR_BACKGROUND
    );
  }
}

void handleKey(uint8_t b)
{
  if (b >= 3) {

    if (numberIndex < NUM_LEN) {
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

  if (b == 1) {

    if (numberIndex > 0) {
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

  if (b == 2) {

    status("Sent value to serial port");

    Serial.printf(
      "[KEY]   +%lums | SEND | buffer=\"%s\"\n",
      millis(),
      numberBuffer
    );

    Serial.println(numberBuffer);
  }

  if (b == 0) {

    numberIndex = 0;
    numberBuffer[0] = 0;

    status("Value cleared");

    Serial.printf(
      "[KEY]   +%lums | NEW | buffer=\"\"\n",
      millis()
    );
  }

  updateDisplay();

  delay(10);
}

void updateKeypad(uint16_t t_x, uint16_t t_y, bool pressed)
{
  for (uint8_t b = 0; b < 15; b++) {

    bool inside = pressed && key[b].contains(t_x, t_y);

    key[b].press(inside);

    if (key[b].justReleased()) {

      if (b < 3) {
        tft.setFreeFont(LABEL1_FONT);
      } else {
        tft.setFreeFont(LABEL2_FONT);
      }

      key[b].drawButton();

      Serial.printf(
        "[KEY]   +%lums | btn=%u \"%s\" | RELEASE\n",
        millis(),
        b,
        keyLabel[b]
      );
    }

    if (key[b].justPressed()) {

      if (b < 3) {
        tft.setFreeFont(LABEL1_FONT);
      } else {
        tft.setFreeFont(LABEL2_FONT);
      }

      key[b].drawButton(true);

      Serial.printf(
        "[KEY]   +%lums | btn=%u \"%s\" | PRESS\n",
        millis(),
        b,
        keyLabel[b]
      );

      handleKey(b);
    }
  }
}

void status(const char *msg)
{
  tft.setTextPadding(SCREEN_WIDTH);
  tft.setTextColor(COLOR_TEXT, COLOR_PANEL);
  tft.setTextFont(0);
  tft.setTextDatum(TC_DATUM);
  tft.setTextSize(1);

  tft.drawString(
    msg,
    STATUS_X,
    STATUS_Y
  );
}