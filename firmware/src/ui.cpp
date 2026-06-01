#include "ui.h"
#include "TFT_eSPI.h"
       

TFT_eSPI tft = TFT_eSPI();


void drawboot(){
    tft.begin();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLUE);
    Serial.println("Display initialized successfully");
}
/*
void drawtext(const char* text, int16_t x, int16_t y, uint32_t color) {
    tft.setTextColor(color);
    tft.drawString(text, x, y, 2);
}
*/

