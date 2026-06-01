//System Libraries
#include <Arduino.h>
#include <Wire.h>

//Firmware headers
#include "gps.h"
#include "navigation.h"
#include "pins.h"
#include "ui.h"
#include "getbattery.h"
#include "flashlight.h"
#include "buttonread.h"
#include "config.h"
#include "readtemperature.h"

bool buttonpressed = true;
int current_page = 0;

// I2C Bus recovery function
void recoverI2C() {
    Serial.println("Attempting I2C bus recovery...");
    pinMode(TEMP_SDA, INPUT_PULLUP);
    pinMode(TEMP_SCL, INPUT_PULLUP);
    delay(100);
    for (int i = 0; i < 10; i++) {
        digitalWrite(TEMP_SCL, HIGH);
        delayMicroseconds(5);
        digitalWrite(TEMP_SCL, LOW);
        delayMicroseconds(5);
    }
    pinMode(TEMP_SDA, INPUT);
    pinMode(TEMP_SCL, INPUT);
    delay(100);
    Serial.println("I2C recovery complete");
}

void setup(){
    // SERIAL INITIALIZATION - DO THIS FIRST
    Serial.begin(115200);
    delay(1000); // Wait for Serial to be ready
    Serial.println("\n\n=== Nomad Firmware Starting ===\n");
    
    // I2C INITIALIZATION (for BME280 and PCF8574)
    Serial.println("Initializing I2C bus...");
    pinMode(TEMP_SDA, INPUT_PULLUP);
    pinMode(TEMP_SCL, INPUT_PULLUP);
    delay(100);
    Wire.begin(TEMP_SDA, TEMP_SCL);
    Wire.setClock(100000);  // Slow clock for reliability
    delay(200);
    Serial.println("I2C Bus initialized at 100kHz");
    
    // GPS INITIALIZATION
    Serial.println("Initializing GPS UART...");
    gpsSerial.begin(GPS_BAUD, SERIAL_8N1, RXD2, TXD2);
    delay(100);
    Serial.println("Serial 2 started at 9600 baud rate");
    
    // DISPLAY INITIALIZATION - TEMPORARILY DISABLED FOR TESTING
    // Serial.println("Initializing display...");
    // drawboot();
    // delay(500);
    // Serial.println("Display initialized");
    
    // PCF GPIO EXTENDER INITIALISATION
    Serial.println("Initializing PCF8574 GPIO extender (0x20)...");
    int pcf_retries = 3;
    while (!pcf.begin(0x20, &Wire) && pcf_retries > 0) {
        Serial.print("PCF8574 init failed, retrying... (");
        Serial.print(pcf_retries);
        Serial.println(" retries left)");
        recoverI2C();
        Wire.begin(TEMP_SDA, TEMP_SCL);
        Wire.setClock(100000);
        delay(500);
        pcf_retries--;
    }
    
    if (pcf_retries == 0) {
        Serial.println("ERROR: Could not initialize PCF8574 after retries!");
    } else {
        Serial.println("PCF8574 found!");
        for (uint8_t p=0; p<8; p++) {
            pcf.pinMode(p, INPUT_PULLUP);
        }
        Serial.println("PCF8574 pins configured");
    }
    delay(100);

    //TEMPERATURE SENSOR INITIALISATION
    Serial.println("Initializing BME280 temperature sensor (0x76)...");
    int bme_retries = 3;
    while (!bme.begin(0x76, &Wire) && bme_retries > 0) {
        Serial.print("BME280 init failed, retrying... (");
        Serial.print(bme_retries);
        Serial.println(" retries left)");
        recoverI2C();
        Wire.begin(TEMP_SDA, TEMP_SCL);
        Wire.setClock(100000);
        delay(500);
        bme_retries--;
    }
    
    if (bme_retries == 0) {
        Serial.println("ERROR: Could not initialize BME280 after retries!");
    } else {
        Serial.println("BME280 found!");
    }
    delay(100);
    
    //BATTERY MANAGER INITIALIZATION
    Serial.println("Initializing MAX17048 battery manager...");
    if (!maxlipo.begin()) {
        Serial.println("ERROR: Couldnt find Adafruit MAX17048? Make sure a battery is plugged in!");
    } else {
        Serial.print(F("Found MAX17048 with Chip ID: 0x")); 
        Serial.println(maxlipo.getChipID(), HEX);
    }
    delay(100);
    
    Serial.println("=== Setup Complete ===\n");
}


void loop(){

    // If the GPIO extender INT pin is pressed, we ask to the nav funciton to actualize the current page of the menu
    if (!digitalRead(INT)) {
        current_page = nav(readbutton(),current_page);  
        Serial.println(current_page);
        buttonpressed = true;
    }else{buttonpressed = false;}

    if (current_page == 21){
        updateGPS();
        if (isGPSValid()) {
            double latitude = getLatitude();
            double longitude = getLongitude();
            double speed = getSpeed();
            double altitude = getAltitude();
            uint32_t satellites = getSatellites();
            // Now you can use and store these values
            Serial.print("LAT: "); Serial.println(latitude, 6);
            Serial.print("LONG: "); Serial.println(longitude, 6);
            Serial.print("SPEED (km/h): "); Serial.println(speed);
            Serial.print("ALT (m): "); Serial.println(altitude);
            Serial.print("Satellites: "); Serial.println(satellites);
            Serial.print("Time: "); Serial.println(getDateTime());
        } else {
            Serial.println(">> Waiting for GPS lock (satellite acquisition)...");
        }
    } else if (current_page == 1){

        Serial.print("Temperature = ");
        Serial.print(readTemperature());
        Serial.println(" *C");
        
        Serial.print("Pressure = ");
        Serial.print(readPressure());
        Serial.println(" hPa");
        
        Serial.print("Humidity = ");
        Serial.print(readHumidity());
        Serial.println(" %");
        Serial.println();
    
    }

    else if (current_page == 41){
        Serial.println("This is a survival advice");
    }

        else if (current_page == 51){
            float cellVoltage = getbattery();
            float cellPercentage = maxlipo.cellPercent();
            Serial.print(F("Batt Voltage: ")); Serial.print(cellVoltage, 3); Serial.println(" V");
            Serial.print(F("Batt Percent: ")); Serial.print(cellPercentage, 1); Serial.println(" %");
            Serial.println();

    }


    


    

    delay(300);
    }
