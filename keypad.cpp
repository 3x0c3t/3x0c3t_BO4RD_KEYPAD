#include "keypad.h"
#include "config.h"

// ============================================================
// 3x0c3t BO4RD KEYPAD
// UI / Keypad
// ============================================================

// Instance TFT définie dans KEYPAD.ino
extern TFT_eSPI tft;

// ------------------------------------------------------------
// Labels
// ------------------------------------------------------------

char keyLabel[15][6] = {
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

// ------------------------------------------------------------
// Couleurs des boutons
// ------------------------------------------------------------

uint16_t keyColor[15] = {
  UI_ERROR,       // New
  UI_PANEL,       // Del
  UI_OK,          // Send

  UI_ACTION,      // 1
  UI_ACTION,      // 2
  UI_ACTION,      // 3
  UI_ACTION,      // 4
  UI_ACTION,      // 5
  UI_ACTION,      // 6
  UI_ACTION,      // 7
  UI_ACTION,      // 8
  UI_ACTION,      // 9
  UI_ACTION,      // .
  UI_ACTION,      // 0
  UI_ACTION       // #
};

// ------------------------------------------------------------
// Boutons TFT_eSPI
// ------------------------------------------------------------

TFT_eSPI_Button key[15];

// ------------------------------------------------------------
// Buffer clavier
// ------------------------------------------------------------

char numberBuffer[NUM_LEN + 1] = "";
uint8_t numberIndex = 0;

// ============================================================
// Style d'un bouton
// ============================================================

void drawButtonStyle(uint8_t b, bool pressed)
{
  if (b >= 15) return;

  int16_t x;
  int16_t y;
  uint16_t w;
  uint16_t h;

  // Positions identiques à celles utilisées dans drawKeypad()
  uint8_t row = b / 3;
  uint8_t col = b % 3;

  x = KEY_X + col * (KEY_W + KEY_SPACING_X);
  y = KEY_Y + row * (KEY_H + KEY_SPACING_Y);

  w = KEY_W;
  h = KEY_H;

  uint16_t fillColor;
  uint16_t outlineColor;
  uint16_t textColor;

  // ----------------------------------------------------------
  // Couleurs selon le type de bouton
  // ----------------------------------------------------------

  if (b == 0) {
    // NEW
    fillColor = pressed ? TFT_RED : UI_ERROR;
    outlineColor = TFT_RED;
    textColor = UI_TEXT;
  }
  else if (b == 1) {
    // DEL
    fillColor = pressed ? TFT_LIGHTGREY : UI_PANEL;
    outlineColor = UI_TEXT_SECONDARY;
    textColor = UI_TEXT;
  }
  else if (b == 2) {
    // SEND
    fillColor = pressed ? TFT_DARKGREEN : UI_OK;
    outlineColor = UI_OK;
    textColor = UI_TEXT;
  }
  else {
    // Touches numériques
    fillColor = pressed ? TFT_CYAN : UI_ACTION;
    outlineColor = UI_ACCENT;
    textColor = UI_TEXT;
  }

  // ----------------------------------------------------------
  // Effacement de l'ancien bouton
  // ----------------------------------------------------------

  tft.fillRoundRect(
    x,
    y,
    w,
    h,
    5,
    fillColor
  );

  tft.drawRoundRect(
    x,
    y,
    w,
    h,
    5,
    outlineColor
  );

  // ----------------------------------------------------------
  // Texte
  // ----------------------------------------------------------

  tft.setTextDatum(MC_DATUM);

  // Police intégrée TFT_eSPI.
  // Pas de GFXFF ici, puisque cette constante n'est pas
  // disponible dans toutes les configurations TFT_eSPI.
  tft.setTextFont(2);
  tft.setTextSize(1);

  tft.setTextColor(
    textColor,
    fillColor
  );

  tft.drawString(
    keyLabel[b],
    x + (w / 2),
    y + (h / 2)
  );

  tft.setTextDatum(TL_DATUM);
}

// ============================================================
// Dessin du keypad
// ============================================================

void drawKeypad()
{
  Serial.println("[UI] drawing keypad");

  for (uint8_t row = 0; row < 5; row++) {

    for (uint8_t col = 0; col < 3; col++) {

      uint8_t b = col + row * 3;

      if (b >= 15) continue;

      uint16_t x =
        KEY_X + col * (KEY_W + KEY_SPACING_X);

      uint16_t y =
        KEY_Y + row * (KEY_H + KEY_SPACING_Y);

      // Initialisation logique du bouton.
      //
      // TFT_eSPI_Button demande un char* et non const char*.
      // keyLabel est donc volontairement un tableau de char.
      key[b].initButton(
        &tft,
        x + KEY_W / 2,
        y + KEY_H / 2,
        KEY_W,
        KEY_H,
        UI_ACCENT,
        keyColor[b],
        UI_TEXT,
        keyLabel[b],
        1
      );

      drawButtonStyle(b, false);

      Serial.printf(
        "[UI] btn=%u \"%s\" | x=%u y=%u w=%u h=%u\n",
        b,
        keyLabel[b],
        x,
        y,
        KEY_W,
        KEY_H
      );
    }
  }

  Serial.println("[UI] keypad OK");
}

// ============================================================
// Affichage de la valeur saisie
// ============================================================

void updateDisplay()
{
  // Zone d'affichage
  tft.fillRoundRect(
    DISPLAY_X,
    DISPLAY_Y,
    DISPLAY_W,
    DISPLAY_H,
    5,
    UI_PANEL
  );

  tft.drawRoundRect(
    DISPLAY_X,
    DISPLAY_Y,
    DISPLAY_W,
    DISPLAY_H,
    5,
    UI_ACCENT
  );

  // Petite indication
  tft.setTextDatum(TL_DATUM);
  tft.setTextFont(1);
  tft.setTextSize(1);

  tft.setTextColor(
    UI_TEXT_SECONDARY,
    UI_PANEL
  );

  tft.drawString(
    "INPUT",
    DISPLAY_X + 6,
    DISPLAY_Y + 5
  );

  // Valeur
  tft.setTextDatum(MR_DATUM);

  tft.setTextFont(2);
  tft.setTextSize(1);

  tft.setTextColor(
    UI_VALUE,
    UI_PANEL
  );

  tft.drawString(
    numberBuffer,
    DISPLAY_X + DISPLAY_W - 7,
    DISPLAY_Y + DISPLAY_H / 2 + 4
  );

  tft.setTextDatum(TL_DATUM);
}

// ============================================================
// Gestion du clavier tactile
// ============================================================

void updateKeypad(
  uint16_t t_x,
  uint16_t t_y,
  bool pressed
)
{
  // ----------------------------------------------------------
  // Mise à jour des états des boutons
  // ----------------------------------------------------------

  for (uint8_t b = 0; b < 15; b++) {

    bool hit =
      pressed &&
      key[b].contains(t_x, t_y);

    key[b].press(hit);
  }

  // ----------------------------------------------------------
  // Détection des événements
  // ----------------------------------------------------------

  for (uint8_t b = 0; b < 15; b++) {

    if (key[b].justPressed()) {

      Serial.printf(
        "[KEY] PRESS | btn=%u | \"%s\" | touch=%u,%u | value=\"%s\"\n",
        b,
        keyLabel[b],
        t_x,
        t_y,
        numberBuffer
      );

      drawButtonStyle(b, true);

      // ------------------------------------------------------
      // Touches numériques
      // ------------------------------------------------------

      if (b >= 3) {

        if (numberIndex < NUM_LEN) {

          numberBuffer[numberIndex] =
            keyLabel[b][0];

          numberIndex++;

          numberBuffer[numberIndex] = '\0';

          Serial.printf(
            "[KEY] INPUT | \"%s\" | len=%u\n",
            numberBuffer,
            numberIndex
          );
        }

        updateDisplay();
      }

      // ------------------------------------------------------
      // DEL
      // ------------------------------------------------------

      if (b == 1) {

        if (numberIndex > 0) {
          numberIndex--;

          numberBuffer[numberIndex] = '\0';
        }

        Serial.printf(
          "[KEY] DELETE | value=\"%s\" | len=%u\n",
          numberBuffer,
          numberIndex
        );

        updateDisplay();
      }

      // ------------------------------------------------------
      // SEND
      // ------------------------------------------------------

      if (b == 2) {

        Serial.printf(
          "[KEY] SEND | value=\"%s\" | len=%u\n",
          numberBuffer,
          numberIndex
        );

        status("SENT");

        Serial.print("[DATA] ");
        Serial.println(numberBuffer);
      }

      // ------------------------------------------------------
      // NEW
      // ------------------------------------------------------

      if (b == 0) {

        numberIndex = 0;
        numberBuffer[0] = '\0';

        Serial.println("[KEY] NEW | input cleared");

        updateDisplay();
      }
    }

    // --------------------------------------------------------
    // Relâchement
    // --------------------------------------------------------

    if (key[b].justReleased()) {

      Serial.printf(
        "[KEY] RELEASE | btn=%u | \"%s\"\n",
        b,
        keyLabel[b]
      );

      drawButtonStyle(b, false);
    }
  }
}

// ============================================================
// Barre de statut
// ============================================================

void status(const char *msg)
{
  // Zone de statut sous l'affichage.
  // Elle ne doit surtout pas recouvrir les boutons New / Del /
  // Send. Les humains ont déjà assez de problèmes avec les
  // rectangles qui se dessinent au mauvais endroit.

  tft.fillRect(
    STATUS_X - STATUS_W / 2,
    STATUS_Y,
    STATUS_W,
    STATUS_H,
    UI_BG
  );

  tft.setTextDatum(MC_DATUM);

  tft.setTextFont(1);
  tft.setTextSize(1);

  tft.setTextColor(
    UI_TEXT_SECONDARY,
    UI_BG
  );

  tft.drawString(
    msg,
    STATUS_X,
    STATUS_Y + STATUS_H / 2
  );

  tft.setTextDatum(TL_DATUM);

  Serial.printf(
    "[UI] STATUS | \"%s\"\n",
    msg
  );
}