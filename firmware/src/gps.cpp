#include "TinyGPSPlus.h"
#include "config.h"
#include "gps.h"

TinyGPSPlus gps;
HardwareSerial gpsSerial(2);
static unsigned long lastPrint = 0;
static unsigned long sentencesProcessed = 0;


void readgps() {
  while (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read());
  }

  if (millis() - lastPrint > 2000) {
    lastPrint = millis();
    
    Serial.println("=== GPS STATUS ===");
    Serial.print("Sentences processed: ");
    Serial.println(gps.sentencesWithFix());
    Serial.print("Satellites: ");
    Serial.println(gps.satellites.value());
    Serial.print("HDOP: ");
    Serial.println(gps.hdop.value() / 100.0);

    // Check if we have a valid fix
    if (gps.location.isValid()) {
      Serial.print("LAT: ");
      Serial.println(gps.location.lat(), 6); 
      Serial.print("LONG: "); 
      Serial.println(gps.location.lng(), 6);
      Serial.print("SPEED (km/h) = "); 
      Serial.println(gps.speed.kmph()); 
      Serial.print("ALT (m) = "); 
      Serial.println(gps.altitude.meters());
      Serial.print("Time in UTC: ");
      Serial.println(String(gps.date.year()) + "/" + String(gps.date.month()) + "/" + String(gps.date.day()) + "," + String(gps.time.hour()) + ":" + String(gps.time.minute()) + ":" + String(gps.time.second()));
    } else {
      Serial.println(">> Waiting for GPS lock (satellite acquisition)...");
    }
    Serial.println("");
  }
}