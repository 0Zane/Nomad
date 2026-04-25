#include <Arduino.h>
#include "buttonread.h"


bool readbuttondown (int pin){


    if(digitalRead(pin) == 0){

        Serial.println("Down button pressed !");
        digitalWrite(7, 1);
        return 1;
    }else{

        digitalWrite(7, 0);
        return 0;
    }

}




bool readbuttonleft (int pin){


    if(digitalRead(pin) == 0){

        Serial.println(" Left button pressed !");
        digitalWrite(7, 1);
        return 1;
        
    }else{

        digitalWrite(7, 0);
        return 0;
    }

}
bool readbuttonright (int pin){


    if(digitalRead(pin) == 0){

        Serial.println(" Right button pressed !");
        digitalWrite(7, 1);
        return 1;
        
    }else{

        digitalWrite(7, 0);
        return 0;
    }

}
bool readbuttonup (int pin){

    if(digitalRead(pin) == 0){

        Serial.println(" Up button pressed !");
        digitalWrite(7, 1);
        return 1;
        
    }else{

        digitalWrite(7, 0);
        return 0;
    }

}




bool readbuttonselect (int pin){

    if(digitalRead(pin) == 0){

        Serial.println(" Select button pressed !");
        digitalWrite(7, 1);
        
        return 1;         
        
    }else{

        digitalWrite(7, 0);
        return 0;
    }


}
