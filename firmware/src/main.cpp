//System Libraries
#include <Arduino.h>
#include <Wire.h>

//Features Libraries
#include "readtemperature.h"
#include "Adafruit_BME280.h"
#include "Adafruit_PCF8574.h"
#include "Adafruit_MAX1704X.h"
#include "TFT_eSPI.h"

//Firmware headers
#include "gps.h"
#include "navigation.h"
#include "pins.h"
#include "ui.h"
#include "getbattery.h"
#include "flashlight.h"
#include "buttonread.h"
#include "config.h"

bool buttonpressed = true;
int current_page = 0;

void setup(){
    // PCF GPIO EXTENDER INITIALISATION
    if (!pcf.begin(0x20, &Wire)) {
        Serial.println("Couldn't find PCF8574");
    }
    for (uint8_t p=0; p<8; p++) {
        pcf.pinMode(p, INPUT_PULLUP);
    }

    //TEMPERATURE SENSOR INITIALISATION
    if (!bme.begin(0x76, &Wire)) {
        Serial.println("Could not find a valid BME280 sensor, check wiring!");
        }
        
    //GPS INITIALIZATION
    gpsSerial.begin(GPS_BAUD, SERIAL_8N1, RXD2, TXD2);
    Serial.println("Serial 2 started at 9600 baud rate");
    Serial.begin(9600);
    
    //BATTERY MANAGER INITIALIZATION
    if (!maxlipo.begin()) {
    Serial.println(F("Couldnt find Adafruit MAX17048? Make sure a battery is plugged in!"));
    }  else {Serial.print(F("Found MAX17048"));
    Serial.print(F(" with Chip ID: 0x")); 
    Serial.println(maxlipo.getChipID(), HEX);}

    }


void loop(){

    // If the GPIO extender INT pin is pressed, we ask to the nav funciton to actualize the current page of the menu
    if (!digitalRead(INT)) {
        current_page = nav(readbutton(),current_page);  
        Serial.println(current_page);
        buttonpressed = true;
    }else{buttonpressed = false;}

    if (current_page == 21){
        updateGPS();
        if (isGPSValid()) {
            double latitude = getLatitude();
            double longitude = getLongitude();
            double speed = getSpeed();
            double altitude = getAltitude();
            uint32_t satellites = getSatellites();
            // Now you can use and store these values
            Serial.print("LAT: "); Serial.println(latitude, 6);
            Serial.print("LONG: "); Serial.println(longitude, 6);
            Serial.print("SPEED (km/h): "); Serial.println(speed);
            Serial.print("ALT (m): "); Serial.println(altitude);
            Serial.print("Satellites: "); Serial.println(satellites);
            Serial.print("Time: "); Serial.println(getDateTime());
        } else {
            Serial.println(">> Waiting for GPS lock (satellite acquisition)...");
        }
    } else if (current_page == 1){

        Serial.print("Temperature = ");
        Serial.print(readTemperature());
        Serial.println(" *C");
        
        Serial.print("Pressure = ");
        Serial.print(readPressure());
        Serial.println(" hPa");
        
        Serial.print("Humidity = ");
        Serial.print(readHumidity());
        Serial.println(" %");
        Serial.println();
    
    }

    else if (current_page == 41){
        Serial.println("This is a survival advice");
    }

        else if (current_page == 51){
            float cellVoltage, cellPercentage = getbattery();
            Serial.print(F("Batt Voltage: ")); Serial.print(cellVoltage, 3); Serial.println(" V");
            Serial.print(F("Batt Percent: ")); Serial.print(cellPercentage, 1); Serial.println(" %");
            Serial.println();

    }


    


    

    delay(300);
    }
