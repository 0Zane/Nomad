#include "ui.h"
#include "TFT_eSPI.h"
#include <SPI.h>

TFT_eSPI tft = TFT_eSPI();

void drawboot() {
    Serial.println("Starting TFT initialization...");
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLUE);
    Serial.println("Display initialized successfully");
}



