#include <Arduino.h>
#include "pins.h"
#include "flashlight.h"

void flashlight(bool light_state){


    digitalWrite(FLASHLIGHT,light_state);
    
}