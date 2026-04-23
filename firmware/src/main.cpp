#include <Arduino.h>

#include "features.h"

float readtemp(int);

void setup(){

    Serial.begin(9600);


}


void loop(){
    Serial.println("Nomad test1");
    Serial.println(readtemp());
    delay(1000);


}