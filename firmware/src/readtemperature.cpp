#include "Adafruit_BME280.h"
#include <Wire.h>
#include "readtemperature.h"

Adafruit_BME280 bme;


float readTemperature(){
    return bme.readTemperature();
}

float readPressure(){
    return bme.readPressure() / 100.0F;
}

float readHumidity(){
    return bme.readHumidity();
}