#include "features.h"
#include <DHT.h>



#define DHTTYPE DHT11
#define DHTPIN 2
float readtemp(){
    DHT dht(DHTPIN, DHTTYPE);
    float temp = dht.readTemperature();

    return temp;
    
}