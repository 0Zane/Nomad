#include <Arduino.h>
#include <Wire.h>
#include "flashlight.h"
#include "buttonread.h"
#include "config.h"
#include "readtemperature.h"
#include "Adafruit_MCP9808.h"
#include "Adafruit_PCF8574.h"
#include "gps.h"



Adafruit_PCF8574 pcf;
bool buttonpressed = true;

void flashlight(bool);
int readbutton();
void readgps();

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

    if (!digitalRead(10)) {
        int pressed_button = readbutton();
        if(pressed_button != -1)
        Serial.println(pressed_button);
    }
    


    
    readgps();

    delay(100);
    }
