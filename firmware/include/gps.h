#include "TinyGPSPlus.h"
#include "pins.h"

#define GPS_BAUD 9600
extern TinyGPSPlus gps;
extern HardwareSerial gpsSerial;

// Update GPS data from serial
void updateGPS();

// GPS data getters
bool isGPSValid();
uint32_t getSatellites();
double getHDOP();
double getLatitude();
double getLongitude();
double getSpeed();
double getAltitude();
String getDateTime();