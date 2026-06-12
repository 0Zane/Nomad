#include <Arduino.h>
#include <math.h>
#include "ui.h"
#include <TFT_eSPI.h>
#include "icon.h"

TFT_eSPI tft = TFT_eSPI();

void drawboot(){
    Serial.println("Drawing booting screen...");
    tft.fillScreen(TFT_BLACK);
    int x = (tft.width() - 300) / 2;
    int y = (tft.height() - 144) / 2;
    tft.setSwapBytes(true);
    tft.pushImage(x, y, 300, 144, logo);
    Serial.println("BLUE SCREEN HAS BEEN INITIALIZED");
}


void drawenv(){}

void drawflashlight(){}

void drawgps(){}

void drawlora(){}

void drawtips(){}

void drawdevice(){}