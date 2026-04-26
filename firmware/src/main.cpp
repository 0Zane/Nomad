#include <Arduino.h>
#include <Wire.h>
#include "readtemperature.h"
#include "flashlight.h"

float readtemp();
void flashlight(bool);
bool readbuttondown (int pin);
bool readbuttonleft (int pin);
bool readbuttonright (int pin);
bool readbuttonup (int pin);
bool readbuttonselect (int pin);
bool  initTempSensor();

void setup(){


    if (!initTempSensor()) {
        Serial.println("MCP9808 not found!");
    } else {
        Serial.println("MCP9808 Ready.");
    }
    
    Serial.begin(9600);
    pinMode(1, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(15, OUTPUT); // RED LED
    pinMode(47, INPUT);
    pinMode(45, INPUT);
    pinMode(18, INPUT);
    pinMode(8, INPUT);
    pinMode(17, INPUT);
    Wire.begin(21,20);
}


void loop(){
    readbuttondown (47);
    readbuttonleft (18);
    readbuttonright (8);
    readbuttonup (17);
    readbuttonselect (45);

    if (readbuttonselect (45)){

        Serial.println(readtemp());
    }

    delay(100);
    }
