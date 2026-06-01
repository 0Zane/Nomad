#include "TinyGPSPlus.h"
#include "config.h"
#include "gps.h"

// The TinyGPS++ object
TinyGPSPlus gps;
HardwareSerial gpsSerial(2);

// Update GPS data from serial
void updateGPS() {
  while (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read());
  }
}

// Check if GPS has a valid fix
bool isGPSValid() {
  return gps.location.isValid();
}

// Get number of satellites
uint32_t getSatellites() {
  return gps.satellites.value();
}

// Get HDOP value (Horizontal Dilution of Precision)
double getHDOP() {
  return gps.hdop.value() / 100.0;
}

// Get latitude
double getLatitude() {
  return gps.location.lat();
}

// Get longitude
double getLongitude() {
  return gps.location.lng();
}

// Get speed in km/h
double getSpeed() {
  return gps.speed.kmph();
}

// Get altitude in meters
double getAltitude() {
  return gps.altitude.meters();
}

// Get date and time as string
String getDateTime() {
  return String(gps.date.year()) + "/" + String(gps.date.month()) + "/" + String(gps.date.day()) + "," + 
         String(gps.time.hour()) + ":" + String(gps.time.minute()) + ":" + String(gps.time.second());
}