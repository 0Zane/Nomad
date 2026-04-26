#include <Adafruit_MCP9808.h>
#include <pins.h>
#include <Wire.h>

Adafruit_MCP9808 temperaturesensor = Adafruit_MCP9808();

bool initTempSensor(){

    return temperaturesensor.begin(0x18);
}

float readtemp(){

    float temp = temperaturesensor.readTempC();
    return temp;
    
}