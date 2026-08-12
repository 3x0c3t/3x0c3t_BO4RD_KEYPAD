#ifndef CONFIG_H
#define CONFIG_H

#include <TFT_eSPI.h>

#define CALIBRATION_FILE "/TouchCalData1"

#define REPEAT_CAL false

#define KEY_X 40
#define KEY_Y 96
#define KEY_W 62
#define KEY_H 30

#define KEY_SPACING_X 18
#define KEY_SPACING_Y 20

#define KEY_TEXTSIZE 1

#define LABEL1_FONT &FreeSansOblique12pt7b
#define LABEL2_FONT &FreeSansBold12pt7b

#define DISP_X 1
#define DISP_Y 10
#define DISP_W 238
#define DISP_H 50

#define DISP_TSIZE 3
#define DISP_TCOLOR TFT_CYAN

#define NUM_LEN 12

#define STATUS_X 120
#define STATUS_Y 65

extern TFT_eSPI tft;

#endif