#include "Adafruit_MAX1704X.h"
#include <Arduino.h>
#include "getbattery.h"

Adafruit_MAX17048 maxlipo;

float getbattery(){
    float cellVoltage = maxlipo.cellVoltage();
    if (isnan(cellVoltage)) {
        Serial.println("Failed to read cell voltage, check battery is connected!");
        delay(2000);
        return 0.00;
    }
    return cellVoltage;
}