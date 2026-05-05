#include "Adafruit_BME280.h"
#include <Wire.h>
#include "readtemperature.h"


extern Adafruit_BME280 bme;  

void readtemp(){

    Serial.print("Temperature = ");
    Serial.print(bme.readTemperature());
    Serial.println(" *C");

    Serial.print("Pressure = ");

    Serial.print(bme.readPressure() / 100.0F);
    Serial.println(" hPa");

    Serial.print("Humidity = ");
    Serial.print(bme.readHumidity());
    Serial.println(" %");

    Serial.println();
    
}