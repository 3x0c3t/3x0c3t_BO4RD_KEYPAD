#include "keypad.h"
#include "config.h"

extern TFT_eSPI tft;

TFT_eSPI_Button key[15];

char keyLabel[15][6] = {
  "New", "Del", "Send",
  "1", "2", "3",
  "4", "5", "6",
  "7", "8", "9",
  ".", "0", "#"
};

uint16_t keyColor[15] = {
  UI_ERROR,
  UI_PANEL,
  UI_OK,
  UI_ACTION,
  UI_ACTION,
  UI_ACTION,
  UI_ACTION,
  UI_ACTION,
  UI_ACTION,
  UI_ACTION,
  UI_ACTION,
  UI_ACTION,
  UI_ACTION,
  UI_ACTION,
  UI_ACTION
};

uint16_t keyX[15];
uint16_t keyY[15];

char numberBuffer[NUM_LEN + 1] = "";
uint8_t numberIndex = 0;

void initKeypad()
{
  drawKeypad();
  updateDisplay();

  Serial.println("[UI] keypad READY");
}

void drawButtonStyle(uint8_t b, bool pressed)
{
  if (b >= 15)
    return;

  uint16_t fillColor = keyColor[b];

  if (pressed)
    fillColor = UI_ACCENT;

  tft.setFreeFont(LABEL2_FONT);

  key[b].initButton(
    &tft,
    keyX[b],
    keyY[b],
    KEY_W,
    KEY_H,
    UI_ACCENT,
    fillColor,
    UI_TEXT,
    keyLabel[b],
    KEY_TEXTSIZE
  );

  key[b].drawButton(pressed);
}

void drawKeypad()
{
  uint8_t b = 0;

  for (uint8_t row = 0; row < 5; row++)
  {
    for (uint8_t col = 0; col < 3; col++)
    {
      b = col + row * 3;

      keyX[b] = KEY_X + col * (KEY_W + KEY_SPACING_X);
      keyY[b] = KEY_Y + row * (KEY_H + KEY_SPACING_Y);

      drawButtonStyle(b, false);

      Serial.printf(
        "[UI] btn=%u \"%s\" | x=%u y=%u w=%u h=%u\n",
        b,
        keyLabel[b],
        keyX[b],
        keyY[b],
        KEY_W,
        KEY_H
      );
    }
  }
}

void updateDisplay()
{
  tft.fillRect(
    DISPLAY_X,
    DISPLAY_Y,
    DISPLAY_W,
    DISPLAY_H,
    UI_PANEL
  );

  tft.drawRect(
    DISPLAY_X,
    DISPLAY_Y,
    DISPLAY_W,
    DISPLAY_H,
    UI_ACCENT
  );

  tft.setFreeFont(LABEL2_FONT);
  tft.setTextDatum(TR_DATUM);
  tft.setTextColor(UI_VALUE, UI_PANEL);

  tft.drawString(
    numberBuffer,
    DISPLAY_X + DISPLAY_W - 8,
    DISPLAY_Y + 7
  );

  tft.setTextDatum(TL_DATUM);
}

void updateKeypad(uint16_t t_x, uint16_t t_y, bool pressed)
{
  for (uint8_t b = 0; b < 15; b++)
  {
    bool inside = false;

    if (pressed)
    {
      int16_t left = keyX[b] - KEY_W / 2;
      int16_t top = keyY[b] - KEY_H / 2;

      inside =
        t_x >= left &&
        t_x < left + KEY_W &&
        t_y >= top &&
        t_y < top + KEY_H;
    }

    key[b].press(inside);

    if (key[b].justPressed())
    {
      drawButtonStyle(b, true);

      if (b >= 3)
      {
        if (numberIndex < NUM_LEN)
        {
          numberBuffer[numberIndex] = keyLabel[b][0];
          numberIndex++;
          numberBuffer[numberIndex] = '\0';
        }

        status("");
      }

      if (b == 1)
      {
        if (numberIndex > 0)
        {
          numberIndex--;
          numberBuffer[numberIndex] = '\0';
        }

        status("");
      }

      if (b == 2)
      {
        status("VALUE SENT");
        Serial.printf(
          "[KEYPAD] SEND | value=\"%s\" | len=%u\n",
          numberBuffer,
          numberIndex
        );
        Serial.println(numberBuffer);
      }

      if (b == 0)
      {
        numberIndex = 0;
        numberBuffer[0] = '\0';

        status("VALUE CLEARED");

        Serial.println("[KEYPAD] NEW | buffer cleared");
      }

      updateDisplay();

      delay(10);
    }

    if (key[b].justReleased())
    {
      drawButtonStyle(b, false);
    }
  }
}

void status(const char *msg)
{
  tft.fillRect(
    0,
    STATUS_Y,
    SCREEN_WIDTH,
    14,
    UI_BG
  );

  tft.setTextPadding(SCREEN_WIDTH);
  tft.setTextDatum(TC_DATUM);
  tft.setTextColor(UI_TEXT_SECONDARY, UI_BG);
  tft.setTextFont(0);
  tft.setTextSize(1);

  tft.drawString(
    msg,
    STATUS_X,
    STATUS_Y
  );

  tft.setTextPadding(0);
  tft.setTextDatum(TL_DATUM);
}