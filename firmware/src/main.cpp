#include <Arduino.h>
#include <Wire.h>
#include "flashlight.h"
#include "buttonread.h"
#include "config.h"
#include "readtemperature.h"
#include "Adafruit_BME280.h"
#include "Adafruit_PCF8574.h"
#include "gps.h"
#include "navigation.h"
#include "pins.h"
#include "Adafruit_MAX1704X.h"

Adafruit_MAX17048 maxlipo;
Adafruit_BME280 bme;  
Adafruit_PCF8574 pcf;
bool buttonpressed = true;

float getbattery();
void flashlight(bool);
int readbutton();
void readgps();
int nav(int, int);
void readtemp();
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
        readgps();
    } else if (current_page == 1){

        readtemp();
    
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
