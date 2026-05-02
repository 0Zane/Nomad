#include <Arduino.h>
#include <Wire.h>
#include "flashlight.h"
#include "buttonread.h"
#include "config.h"
#include "readtemperature.h"
#include "Adafruit_MCP9808.h"
#include "Adafruit_PCF8574.h"
#include "gps.h"
#include "navigation.h"


Adafruit_PCF8574 pcf;
bool buttonpressed = true;

void flashlight(bool);
int readbutton();
void readgps();
int nav(int, int);

int current_page = 0;

void setup(){
    
    // PCF GPIO EXTENDER INITIALISATION
    if (!pcf.begin(0x20, &Wire)) {
        Serial.println("Couldn't find PCF8574");
    }
    for (uint8_t p=0; p<8; p++) {
        pcf.pinMode(p, INPUT_PULLUP);
    }

    //MCP9808 INITIALISATION
    if (!temperaturesensor.begin(0x18)) {
        Serial.println("MCP9808 not found!");
    } else {
        Serial.println("MCP9808 Ready.");
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
        Serial.println(readtemp());
    }

    else if (current_page == 41){
        Serial.println("This is a survival advice");
    }


    


    
    //readgps();

    delay(100);
    }
