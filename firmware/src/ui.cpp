#include <Arduino.h>
#include <math.h>
#include "ui.h"
#include <TFT_eSPI.h>
#include "nomadlogo.h"

TFT_eSPI tft = TFT_eSPI();

void drawboot(){
    Serial.println("Drawing booting screen...");
    tft.fillScreen(TFT_BLUE);
    // Try to auto-detect a square image size from the logo data
    size_t len = sizeof(logo) / sizeof(logo[0]);
    int imgW = 200;
    int imgH = 200;
    if (len > 0) {
        int side = (int)sqrt((double)len + 0.5);
        if ((size_t)(side * side) == len) {
            imgW = imgH = side;
        }
    }
    int x = (tft.width() - imgW) / 2;
    int y = (tft.height() - imgH) / 2;
    tft.setSwapBytes(true);
    tft.pushImage(x, y, imgW, imgH, logo);
    Serial.println("BLUE SCREEN HAS BEEN INITIALIZED");
}