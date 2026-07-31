// ============================================================================
// pages.h — Screen drawing functions for every page/subpage of the Nomad UI
// ============================================================================
// This file does NOT modify any existing logic. It only adds new draw
// functions that render each page defined by the state machine in
// navigation.cpp (see the numbering scheme below). Nothing here is wired
// into main.cpp automatically — call drawUIPage(current_page) from the main
// loop (or call the individual draw*/drawPage_* functions directly) whenever
// you want it hooked up.
//
// Paging scheme (matches navigation.cpp):
//   0  = Environment home        1..4  = Temperature, Humidity, Pressure, Altitude
//   10 = Flashlight home         11    = Toggle
//   20 = GPS home                21..26= Latitude, Longitude, Speed, Altitude, HDOP, Satellites
//   30 = LoRa home                31..33= Send OK, Send SOS, Send GPS
//   40 = Tips home                41..45= Tip 1..5
//   50 = Device home              51..53= Battery, Battery life, Hardware info
//
// Style: black background, orange icons/accents, simple flat vector icons
// drawn with basic TFT_eSPI primitives (no external image assets required).
// ============================================================================

#pragma once

#include <Arduino.h>

// ---------------------------------------------------------------------------
// One function per page. Each function is fully self-contained: it clears
// the screen and draws its own header/footer/content. Sensor pages read
// live data directly from the existing sensor modules (gps.h,
// readtemperature.h, getbattery.h, tips.h) so they can be dropped straight
// into the main loop.
// ---------------------------------------------------------------------------

// ----- Environment (0x) -----
void drawPage_EnvironmentHome();        // page 0
void drawPage_EnvironmentTemperature(); // page 1
void drawPage_EnvironmentHumidity();    // page 2
void drawPage_EnvironmentPressure();    // page 3
void drawPage_EnvironmentAltitude();    // page 4

// ----- Flashlight (1x) -----
void drawPage_FlashlightHome();               // page 10
void drawPage_FlashlightToggle(bool isOn);    // page 11

// ----- GPS (2x) -----
void drawPage_GPSHome();        // page 20
void drawPage_GPSLatitude();    // page 21
void drawPage_GPSLongitude();   // page 22
void drawPage_GPSSpeed();       // page 23
void drawPage_GPSAltitude();    // page 24
void drawPage_GPSHDOP();        // page 25
void drawPage_GPSSatellites();  // page 26

// ----- LoRa (3x) -----
void drawPage_LoRaHome();      // page 30
void drawPage_LoRaSendOK();    // page 31
void drawPage_LoRaSendSOS();   // page 32
void drawPage_LoRaSendGPS();   // page 33

// ----- Survival Tips (4x) -----
void drawPage_TipsHome();          // page 40
void drawPage_Tips(int tipIndex);  // pages 41..45 -> tipIndex 0..4

// ----- Device (5x) -----
void drawPage_DeviceHome();          // page 50
void drawPage_DeviceBattery();       // page 51
void drawPage_DeviceBatteryLife();   // page 52
void drawPage_DeviceHardware();      // page 53

// ---------------------------------------------------------------------------
// Convenience dispatcher: draws whatever page number the navigation state
// machine (nav()) currently reports. flashlightOn is only needed for page 11
// since there is no hardware getter for the flashlight state; pass whatever
// your own code is tracking (defaults to false if you don't have it).
// ---------------------------------------------------------------------------
void drawUIPage(int current_page, bool flashlightOn = false);
