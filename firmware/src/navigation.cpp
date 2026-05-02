#include <math.h>

int nav(int button_action, int current_page){

    int submenu_max;

    if (current_page >= 60 || current_page < 0){
        current_page = 0;
    }
    
    if ( current_page % 10 == 0){ // That would mean that we are not in a submenu
        switch (button_action){

            case 1: // Left button pressed
                if (current_page > 0){
                    current_page -= 10;
                } 
                else{
                    current_page = 0;
                }
                break;

            case 3: // Right button pressed
            if (current_page < 50){
                current_page += 10;
            }else {
                current_page = 0;
            }
                break;
                
            case 2: // Select button pressed -> We enter in a submenu
                current_page ++;
                break;
            
            default:
                break;

        }
    }

    else {

        if (floor(current_page / 10) == 0 ){ // we are in Environment
             submenu_max = 4; // temperature, relative humidity, barometric pressure, and altitude, time
            }
        else if (floor(current_page / 10) == 1){ // we are in Flashlight
             submenu_max = 1; //Level of light ( maybe different levels of light in the future)
            }
        else if (floor(current_page / 10) == 2){ // we are in GPS
             submenu_max = 6; // LAT, LON, SPE, ALT, HDOP, SAT
                }
        else if (floor(current_page / 10) == 3){ // we are in LoRa
             submenu_max = 3; // Messages: OK | SOS | GPS
            }
        else if (floor(current_page / 10) == 4){ // we are in Tips
             submenu_max = 5; // (Non definitive value) Device guide, make a fire, cook animals, call for rescue, regulate temperature
            }
        else if (floor(current_page / 10) == 5){ // we are in device
             submenu_max = 3; // Battery pourcentage left, approximative battery life, hardware of the device 
            }
        switch (button_action)
        {
        case  0: //down button pressed
            if (current_page%10 <= submenu_max)
            current_page ++;
            else{
                current_page = floor(current_page/10) +1;
            }
            break;
        case 1: //up button pressed
            if (current_page % 10 >1)
            current_page --;
            break;

        case 2: //left
            current_page -= current_page % 10;
            break;

        case 3: // right
            current_page -= current_page % 10;
        default:
            break;
        }

    }

    return current_page;

}

/*
0 = Environment
1 = Flashlight 
2 = GPS
3 = LoRa
4 = Tips
5 = Device
*/