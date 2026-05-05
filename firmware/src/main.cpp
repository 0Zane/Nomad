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

Adafruit_BME280 bme;  
Adafruit_PCF8574 pcf;
bool buttonpressed = true;

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

    //BME280 INITIALISATION
    if (!bme.begin(0x76, &Wire)) {
        Serial.println("Could not find a valid BME280 sensor, check wiring!");
        }
        
    //GPS INITIALIZATION
    gpsSerial.begin(GPS_BAUD, SERIAL_8N1, RXD2, TXD2);
    Serial.println("Serial 2 started at 9600 baud rate");
    Serial.begin(9600);

    

    }


void loop(){

    // If the GPIO extender INT pin is pressed, we ask to the nav funciton to actualize the current page of the menu
    if (!digitalRead(10)) {
        current_page = nav(readbutton(),current_page);  
        Serial.println(current_page);
        buttonpressed = true;
    }else{buttonpressed = false;}

    if (current_page == 21){
        readgps();
    } 

    else if (current_page == 1){




    Serial.print("Temperature = ");
    Serial.print(bme.readTemperature());
    Serial.println(" *C");

    Serial.print("Pressure = ");

    Serial.print(bme.readPressure() / 100.0F);
    Serial.println(" hPa");
/*
    Serial.print("Approx. Altitude = ");
    Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
    Serial.println(" m");
*/
    Serial.print("Humidity = ");
    Serial.print(bme.readHumidity());
    Serial.println(" %");

    Serial.println();
    
    }

    else if (current_page == 41){
        Serial.println("This is a survival advice");
    }


    


    

    delay(100);
    }
