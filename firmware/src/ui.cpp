#include "TFT_eSPI"
#include "nomadlogo.h"
#include "ui.h"


extern TFT_eSPI tft;  
void drawboot(){

    tft.fillScreen(TFT_BLACK);    
    tft.pushImage(0, 0, 170, 100, nomadlogo_map);     
    delay(2000);                       
}


