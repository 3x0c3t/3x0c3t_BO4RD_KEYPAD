#include "keypad.h"
#include "config.h"

TFT_eSPI_Button key[15];

char keyLabel[15][5] =
{
  "New",
  "Del",
  "Send",
  "1",
  "2",
  "3",
  "4",
  "5",
  "6",
  "7",
  "8",
  "9",
  ".",
  "0",
  "#"
};

uint16_t keyColor[15] =
{
  TFT_RED,
  TFT_DARKGREY,
  TFT_DARKGREEN,
  TFT_BLUE,
  TFT_BLUE,
  TFT_BLUE,
  TFT_BLUE,
  TFT_BLUE,
  TFT_BLUE,
  TFT_BLUE,
  TFT_BLUE,
  TFT_BLUE,
  TFT_BLUE,
  TFT_BLUE,
  TFT_BLUE
};

void drawKeypad()
{
  for (uint8_t row = 0; row < 5; row++)
  {
    for (uint8_t col = 0; col < 3; col++)
    {
      uint8_t b = col + row * 3;

      if (b < 3)
      {
        tft.setFreeFont(LABEL1_FONT);
      }
      else
      {
        tft.setFreeFont(LABEL2_FONT);
      }

      key[b].initButton(
        &tft,
        KEY_X + col * (KEY_W + KEY_SPACING_X),
        KEY_Y + row * (KEY_H + KEY_SPACING_Y),
        KEY_W,
        KEY_H,
        TFT_WHITE,
        keyColor[b],
        TFT_WHITE,
        keyLabel[b],
        KEY_TEXTSIZE
      );

      key[b].drawButton();
    }
  }
}

void status(const char *msg)
{
  tft.setTextPadding(SCREEN_WIDTH);

  tft.setTextColor(TFT_WHITE, TFT_DARKGREY);

  tft.setTextFont(0);

  tft.setTextDatum(TC_DATUM);

  tft.setTextSize(1);

  tft.drawString(msg, STATUS_X, STATUS_Y);
}