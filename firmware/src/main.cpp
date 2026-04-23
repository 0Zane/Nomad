#include <Arduino.h>

#include "features.h"

float readtemp(int);
void flashlight(bool);


void setup(){

    Serial.begin(9600);
    pinMode(1, OUTPUT);

}


void loop(){
  
    Serial.println(readtemp());
    flashlight(true);
    delay(1000);
    flashlight(false);
    delay(1000);

}