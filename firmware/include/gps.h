#include <TinyGPS++.h>


#define RXD2 16
#define TXD2 17

#define GPS_BAUD 9600

// The TinyGPS++ object
extern TinyGPSPlus gps;
extern HardwareSerial gpsSerial;
void readgps();