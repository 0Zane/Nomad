#include <Arduino.h>
#include "pins.h"

void flashlight(bool state){


    digitalWrite(FLASHLIGHT,state);
    
}