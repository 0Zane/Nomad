#include <Arduino.h>


#include "readtemperature.h"
#include "flashlight.h"

float readtemp();
void flashlight(bool);


void setup(){

    Serial.begin(9600);
    pinMode(1, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(15, OUTPUT); // RED LED
}


void loop(){

    while (Serial.available() ==0 ){
        if(digitalRead(15) == 0){
            digitalWrite(7,0);
            digitalWrite(15,1);
        }
    }
        String command = Serial.readStringUntil('\n');
        digitalWrite(15,0);
        if(digitalRead(7) == 0){

            digitalWrite(7,1);
        }


            if (command == "o"){
                Serial.println("Flashlight_on");
                flashlight(1); 
            }else if (command == "f"){

                flashlight(0);
                Serial.println("Flashlight_off");
            } else if (command == "r"){

                Serial.println(readtemp());
            } else { 
                Serial.println("Unknown command");
                Serial.print(command);
            }


    }
