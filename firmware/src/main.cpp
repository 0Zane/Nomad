#include <Arduino.h>
#include <Wire.h>
#include "flashlight.h"
#include "buttonread.h"
#include "config.h"
#include "Adafruit_MCP9808.h"
#include "Adafruit_PCF8574.h"

Adafruit_PCF8574 pcf;
Adafruit_MCP9808 temperaturesensor = Adafruit_MCP9808();

void flashlight(bool);
int readbutton();


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
        
    Serial.begin(9600);


}

void loop(){
    int pressed_button =readbutton();
    if(pressed_button != -1){
        Serial.println(pressed_button);
    }
  


    float temp = temperaturesensor.readTempC();
    Serial.println(temp);


    delay(1000);
    }
