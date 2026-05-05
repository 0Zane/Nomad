#include "TinyGPSPlus.h"
#include "pins.h"

#define GPS_BAUD 9600

// The TinyGPS++ object
extern TinyGPSPlus gps;
extern HardwareSerial gpsSerial;
void readgps();