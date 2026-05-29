#include "ui.h"
#include "TFT_eSPI.h"
       
extern TFT_eSPI tft;


void drawtext(const char* text, int16_t x, int16_t y, uint32_t color) {
    tft.setTextColor(color);
    tft.drawString(text, x, y, 2);
}


