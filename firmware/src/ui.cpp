#include <Arduino.h>
#include "ui.h"
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

void drawboot(){
    Serial.println("Drawing booting screen...");
    tft.fillScreen(TFT_BLUE);
    Serial.println("BLUE SCREEN HAD BEEN INITIALIZED");
}