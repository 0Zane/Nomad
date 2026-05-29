#include "config.h"
#include "buttonread.h"

Adafruit_PCF8574 pcf;



int readbutton () {

  
  for (uint8_t p=0; p<5; p++) { // Only reading from 0 to 4 included, we only have 5 buttons

    if (! pcf.digitalRead(p)) { // Check if the pin is low (normally pullup)
        return p;
    }
    
    
  }
  return -1;

}
