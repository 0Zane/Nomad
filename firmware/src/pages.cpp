// ============================================================================
// pages.cpp — Screen drawing functions for every page/subpage of the Nomad UI
// ============================================================================
// Standalone UI layer: does not touch navigation.cpp / ui.cpp / main.cpp.
// Target panel: 1.9" SPI IPS ST7789, 170x320, driven through TFT_eSPI.
// Theme: black background, orange flat-vector icons & accents, light grey
// secondary text. Layout is landscape (uses tft.width()/tft.height() so it
// stays correct whatever rotation is set).
// ============================================================================

#include <Arduino.h>
#include <math.h>
#include <string.h>
#include "pages.h"
#include "ui.h"              // extern TFT_eSPI tft;
#include "gps.h"             // updateGPS, getLatitude, getLongitude, ...
#include "readtemperature.h" // readTemperature, readPressure, readHumidity
#include "getbattery.h"      // getbattery, extern maxlipo
#include "tips.h"            // questions[], answers[]

// ---------------------------------------------------------------------------
// Theme
// ---------------------------------------------------------------------------
static const uint16_t UI_BG     = TFT_BLACK;
static const uint16_t UI_ORANGE = 0xFD20; // primary accent (icons, values, titles)
static const uint16_t UI_DIM    = TFT_DARKGREY; // separators / inactive dots
static const uint16_t UI_TEXT   = TFT_LIGHTGREY; // secondary/body text
static const uint16_t UI_WARN   = 0xF800; // TFT_RED, used sparingly (SOS)

static const int HEADER_H = 34;
static const int FOOTER_H = 18;

// Rough placeholder used only for the "estimated battery life" page - the
// MAX17048 fuel gauge has no current sensing, so this is a simple
// percentage-of-a-fixed-runtime guess, not a measurement.
static const float ESTIMATED_FULL_RUNTIME_HOURS = 20.0f;

// ---------------------------------------------------------------------------
// Icon set — simple flat vector icons drawn with basic TFT_eSPI primitives.
// Every icon is drawn centered at (cx, cy) within roughly a 2*r bounding box.
// ---------------------------------------------------------------------------
enum PageIcon {
    ICON_THERMO,
    ICON_HUMIDITY,
    ICON_PRESSURE,
    ICON_MOUNTAIN,
    ICON_FLASHLIGHT,
    ICON_GPS_PIN,
    ICON_SPEED,
    ICON_TARGET,
    ICON_SATELLITE,
    ICON_ANTENNA,
    ICON_CHECK,
    ICON_WARNING,
    ICON_BOOK,
    ICON_BATTERY,
    ICON_CLOCK,
    ICON_CHIP
};

static void drawIcon(PageIcon icon, int cx, int cy, int r, uint16_t color, bool accent = false) {
    switch (icon) {

    case ICON_THERMO: {
        int tubeW = max(4, r / 3);
        int bulbR = r / 2;
        int tubeTop = cy - r;
        int tubeBottom = cy + r - bulbR;
        tft.fillRoundRect(cx - tubeW / 2, tubeTop, tubeW, tubeBottom - tubeTop, tubeW / 2, color);
        tft.fillCircle(cx, cy + r - bulbR, bulbR, color);
        break;
    }

    case ICON_HUMIDITY: {
        tft.fillTriangle(cx, cy - r,
                          cx - (int)(r * 0.7f), cy + (int)(r * 0.3f),
                          cx + (int)(r * 0.7f), cy + (int)(r * 0.3f), color);
        tft.fillCircle(cx, cy + (int)(r * 0.35f), (int)(r * 0.55f), color);
        break;
    }

    case ICON_PRESSURE: {
        tft.drawCircle(cx, cy, r, color);
        tft.drawCircle(cx, cy, r - 1, color);
        float rad = radians(-50);
        int nx = cx + (int)(cos(rad) * (r - 4));
        int ny = cy + (int)(sin(rad) * (r - 4));
        tft.drawLine(cx, cy, nx, ny, color);
        tft.fillCircle(cx, cy, 2, color);
        break;
    }

    case ICON_MOUNTAIN: {
        tft.fillTriangle(cx - r, cy + (int)(r * 0.6f),
                          cx - (int)(r * 0.1f), cy - r,
                          cx + (int)(r * 0.5f), cy + (int)(r * 0.2f), color);
        tft.fillTriangle(cx - (int)(r * 0.2f), cy + (int)(r * 0.3f),
                          cx + (int)(r * 0.35f), cy - (int)(r * 0.6f),
                          cx + r, cy + (int)(r * 0.6f), color);
        break;
    }

    case ICON_FLASHLIGHT: {
        tft.fillRoundRect(cx - r, cy - (int)(r * 0.35f), (int)(r * 1.1f), (int)(r * 0.7f), 3, color);
        tft.fillTriangle(cx + (int)(r * 0.1f), cy - (int)(r * 0.55f),
                          cx + (int)(r * 0.1f), cy + (int)(r * 0.55f),
                          cx + r, cy, color);
        if (accent) { // "on" -> draw beam rays
            for (int i = -1; i <= 1; i++) {
                int y = cy + i * (int)(r * 0.5f);
                tft.drawLine(cx + r + 3, cy, cx + r + 10, y, color);
            }
        }
        break;
    }

    case ICON_GPS_PIN: {
        int headR = (int)(r * 0.6f);
        int headCy = cy - (int)(r * 0.15f);
        tft.fillCircle(cx, headCy, headR, color);
        tft.fillTriangle(cx - (int)(headR * 0.7f), headCy + (int)(headR * 0.4f),
                          cx + (int)(headR * 0.7f), headCy + (int)(headR * 0.4f),
                          cx, cy + r, color);
        tft.fillCircle(cx, headCy, headR / 2, UI_BG);
        break;
    }

    case ICON_SPEED: {
        tft.drawArc(cx, cy, r, r - 4, 30, 330, color, UI_BG, true);
        float rad = radians(160);
        int nx = cx + (int)(cos(rad) * (r - 6));
        int ny = cy + (int)(sin(rad) * (r - 6));
        tft.drawLine(cx, cy, nx, ny, color);
        tft.fillCircle(cx, cy, 2, color);
        break;
    }

    case ICON_TARGET: {
        tft.drawCircle(cx, cy, r, color);
        tft.drawCircle(cx, cy, (int)(r * 0.6f), color);
        tft.fillCircle(cx, cy, (int)(r * 0.15f), color);
        break;
    }

    case ICON_SATELLITE: {
        tft.fillRect(cx - r, cy - 4, (int)(r * 0.45f), 8, color);
        tft.fillRect(cx + (int)(r * 0.55f), cy - 4, (int)(r * 0.45f), 8, color);
        tft.fillRect(cx - 4, cy - 4, 8, 8, color);
        tft.drawLine(cx, cy - 4, cx - (int)(r * 0.4f), cy - r, color);
        tft.fillCircle(cx - (int)(r * 0.4f), cy - r, 1, color);
        break;
    }

    case ICON_ANTENNA: {
        int bx = cx, by = cy + (int)(r * 0.6f);
        tft.fillCircle(bx, by, 2, color);
        tft.drawArc(bx, by, (int)(r * 0.55f), (int)(r * 0.55f) - 2, 210, 330, color, UI_BG, true);
        tft.drawArc(bx, by, r, r - 2, 210, 330, color, UI_BG, true);
        break;
    }

    case ICON_CHECK: {
        for (int d = -1; d <= 1; d++) {
            tft.drawLine(cx - (int)(r * 0.5f) + d, cy, cx - (int)(r * 0.1f) + d, cy + (int)(r * 0.4f), color);
            tft.drawLine(cx - (int)(r * 0.1f) + d, cy + (int)(r * 0.4f), cx + (int)(r * 0.6f) + d, cy - (int)(r * 0.4f), color);
        }
        break;
    }

    case ICON_WARNING: {
        tft.drawTriangle(cx, cy - r, cx - r, cy + (int)(r * 0.7f), cx + r, cy + (int)(r * 0.7f), color);
        tft.fillRect(cx - 1, cy - (int)(r * 0.25f), 2, (int)(r * 0.55f), color);
        tft.fillCircle(cx, cy + (int)(r * 0.5f), 2, color);
        break;
    }

    case ICON_BOOK: {
        tft.fillRoundRect(cx - r, cy - (int)(r * 0.7f), (int)(r * 0.9f), (int)(r * 1.4f), 2, color);
        tft.fillRoundRect(cx + (int)(r * 0.1f), cy - (int)(r * 0.7f), (int)(r * 0.9f), (int)(r * 1.4f), 2, color);
        tft.drawFastVLine(cx, cy - (int)(r * 0.7f), (int)(r * 1.4f), UI_BG);
        break;
    }

    case ICON_BATTERY: {
        tft.drawRoundRect(cx - r, cy - (int)(r * 0.55f), (int)(r * 1.8f), (int)(r * 1.1f), 3, color);
        tft.fillRect(cx + (int)(r * 0.82f), cy - (int)(r * 0.2f), (int)(r * 0.18f), (int)(r * 0.4f), color);
        tft.fillRect(cx - r + 3, cy - (int)(r * 0.55f) + 3, (int)(r * 1.2f), (int)(r * 1.1f) - 6, color);
        break;
    }

    case ICON_CLOCK: {
        tft.drawCircle(cx, cy, r, color);
        tft.drawLine(cx, cy, cx, cy - (int)(r * 0.6f), color);
        tft.drawLine(cx, cy, cx + (int)(r * 0.4f), cy, color);
        tft.fillCircle(cx, cy, 2, color);
        break;
    }

    case ICON_CHIP: {
        int b = (int)(r * 0.6f);
        tft.fillRoundRect(cx - b, cy - b, b * 2, b * 2, 2, color);
        for (int i = -1; i <= 1; i++) {
            int off = i * (int)(r * 0.4f);
            tft.drawFastVLine(cx + off, cy - r, (int)(r * 0.4f), color);
            tft.drawFastVLine(cx + off, cy + b, (int)(r * 0.4f), color);
            tft.drawFastHLine(cx - r, cy + off, (int)(r * 0.4f), color);
            tft.drawFastHLine(cx + b, cy + off, (int)(r * 0.4f), color);
        }
        break;
    }
    }
}

// ---------------------------------------------------------------------------
// Shared layout helpers
// ---------------------------------------------------------------------------

static void drawHeader(const char *title, PageIcon icon) {
    drawIcon(icon, 22, 17, 13, UI_ORANGE);
    tft.setTextFont(4);
    tft.setTextColor(UI_ORANGE, UI_BG);
    tft.setTextDatum(ML_DATUM);
    tft.drawString(title, 44, 18);
    tft.drawFastHLine(0, HEADER_H, tft.width(), UI_DIM);
}

static void drawSubDots(int index, int count) {
    if (count <= 1) return;
    int spacing = 10;
    int totalWidth = (count - 1) * spacing;
    int startX = tft.width() - 12 - totalWidth;
    int y = 9;
    for (int i = 0; i < count; i++) {
        int x = startX + i * spacing;
        if (i == index - 1) tft.fillCircle(x, y, 3, UI_ORANGE);
        else tft.drawCircle(x, y, 3, UI_DIM);
    }
}

static void drawFooterNav(const char *left, const char *right) {
    int H = tft.height();
    int W = tft.width();
    tft.drawFastHLine(0, H - FOOTER_H, W, UI_DIM);
    tft.setTextFont(1);
    tft.setTextColor(UI_DIM, UI_BG);
    tft.setTextDatum(ML_DATUM);
    tft.drawString(left, 6, H - FOOTER_H / 2);
    tft.setTextDatum(MR_DATUM);
    tft.drawString(right, W - 6, H - FOOTER_H / 2);
}

static void drawCategoryDots(int catIndex) {
    int W = tft.width();
    int H = tft.height();
    int count = 6;
    int spacing = 14;
    int totalWidth = (count - 1) * spacing;
    int startX = W / 2 - totalWidth / 2;
    int y = H - FOOTER_H - 12;
    for (int i = 0; i < count; i++) {
        int x = startX + i * spacing;
        if (i == catIndex) tft.fillCircle(x, y, 3, UI_ORANGE);
        else tft.drawCircle(x, y, 3, UI_DIM);
    }
}

// Home / category landing page template
static void drawHomeTemplate(const char *title, const char *subtitle, PageIcon icon, int catIndex) {
    tft.fillScreen(UI_BG);
    int W = tft.width();
    int H = tft.height();
    int cy = H / 2 - 12;

    drawIcon(icon, W / 2, cy - 6, 30, UI_ORANGE);

    tft.setTextFont(4);
    tft.setTextColor(UI_ORANGE, UI_BG);
    tft.setTextDatum(MC_DATUM);
    tft.drawString(title, W / 2, cy + 36);

    tft.setTextFont(2);
    tft.setTextColor(UI_TEXT, UI_BG);
    tft.drawString(subtitle, W / 2, cy + 56);

    drawCategoryDots(catIndex);
    drawFooterNav("<  MENU  >", "SELECT: OPEN");
}

// Big-number reading page template (sensor / status value)
static void drawValueTemplate(const char *categoryTitle, PageIcon icon, int subIndex, int subCount,
                               const char *label, const String &valueStr, const char *unit,
                               bool warn = false, const char *subValue = nullptr) {
    tft.fillScreen(UI_BG);
    drawHeader(categoryTitle, icon);
    drawSubDots(subIndex, subCount);

    int W = tft.width();
    int H = tft.height();

    tft.setTextFont(2);
    tft.setTextColor(UI_TEXT, UI_BG);
    tft.setTextDatum(TC_DATUM);
    tft.drawString(label, W / 2, HEADER_H + 8);

    uint16_t valColor = warn ? UI_DIM : UI_ORANGE;
    bool hasUnit = unit != nullptr && strlen(unit) > 0;

    tft.setTextFont(7);
    int valW = tft.textWidth(valueStr);
    int unitW = 0;
    if (hasUnit) {
        tft.setTextFont(4);
        unitW = tft.textWidth(unit);
    }
    int gap = hasUnit ? 6 : 0;
    int totalW = valW + gap + unitW;
    int startX = W / 2 - totalW / 2;
    int valY = H / 2 + 6;

    tft.setTextFont(7);
    tft.setTextColor(valColor, UI_BG);
    tft.setTextDatum(ML_DATUM);
    tft.drawString(valueStr, startX, valY);

    if (hasUnit) {
        tft.setTextFont(4);
        tft.setTextColor(UI_TEXT, UI_BG);
        tft.setTextDatum(ML_DATUM);
        tft.drawString(unit, startX + valW + gap, valY + 5);
    }

    if (subValue != nullptr) {
        tft.setTextFont(2);
        tft.setTextColor(UI_DIM, UI_BG);
        tft.setTextDatum(TC_DATUM);
        tft.drawString(subValue, W / 2, valY + 28);
    }

    drawFooterNav("<  BACK", "^ v  CYCLE");
}

// Simple word-wrapping text block, returns the Y position after the last line
static int drawWrappedText(const String &text, int x, int y, int maxWidth, int lineHeight,
                            uint8_t font, uint16_t color) {
    tft.setTextFont(font);
    tft.setTextColor(color, UI_BG);
    tft.setTextDatum(TL_DATUM);

    String line = "";
    int cursorY = y;
    int len = text.length();
    int wordStart = 0;

    for (int i = 0; i <= len; i++) {
        if (i == len || text[i] == ' ') {
            String word = text.substring(wordStart, i);
            String test = line.length() ? (line + " " + word) : word;
            if (tft.textWidth(test) > maxWidth && line.length() > 0) {
                tft.drawString(line, x, cursorY);
                cursorY += lineHeight;
                line = word;
            } else {
                line = test;
            }
            wordStart = i + 1;
        }
    }
    if (line.length()) {
        tft.drawString(line, x, cursorY);
        cursorY += lineHeight;
    }
    return cursorY;
}

// ===========================================================================
// ENVIRONMENT (0x)
// ===========================================================================

void drawPage_EnvironmentHome() {
    drawHomeTemplate("ENVIRONMENT", "Climate & altitude data", ICON_THERMO, 0);
}

void drawPage_EnvironmentTemperature() {
    float t = readTemperature();
    bool valid = !isnan(t);
    String val = valid ? String(t, 1) : "--";
    drawValueTemplate("ENVIRONMENT", ICON_THERMO, 1, 4, "TEMPERATURE", val, "C", !valid);
}

void drawPage_EnvironmentHumidity() {
    float h = readHumidity();
    bool valid = !isnan(h);
    String val = valid ? String(h, 1) : "--";
    drawValueTemplate("ENVIRONMENT", ICON_HUMIDITY, 2, 4, "HUMIDITY", val, "%", !valid);
}

void drawPage_EnvironmentPressure() {
    float p = readPressure();
    bool valid = !isnan(p);
    String val = valid ? String(p, 1) : "--";
    drawValueTemplate("ENVIRONMENT", ICON_PRESSURE, 3, 4, "PRESSURE", val, "hPa", !valid);
}

void drawPage_EnvironmentAltitude() {
    float p = readPressure();
    bool valid = !isnan(p) && p > 0;
    float alt = valid ? 44330.0f * (1.0f - pow(p / 1013.25f, 0.1903f)) : 0;
    String val = valid ? String(alt, 0) : "--";
    drawValueTemplate("ENVIRONMENT", ICON_MOUNTAIN, 4, 4, "ALTITUDE (EST.)", val, "m", !valid,
                       "From barometric pressure");
}

// ===========================================================================
// FLASHLIGHT (1x)
// ===========================================================================

void drawPage_FlashlightHome() {
    drawHomeTemplate("FLASHLIGHT", "Torch control", ICON_FLASHLIGHT, 1);
}

void drawPage_FlashlightToggle(bool isOn) {
    tft.fillScreen(UI_BG);
    drawHeader("FLASHLIGHT", ICON_FLASHLIGHT);
    drawSubDots(1, 1);

    int W = tft.width();
    int H = tft.height();
    uint16_t c = isOn ? UI_ORANGE : UI_DIM;

    drawIcon(ICON_FLASHLIGHT, W / 2 - 6, H / 2 - 14, 28, c, isOn);

    tft.setTextFont(4);
    tft.setTextColor(c, UI_BG);
    tft.setTextDatum(MC_DATUM);
    tft.drawString(isOn ? "ON" : "OFF", W / 2, H / 2 + 34);

    drawFooterNav("<  BACK", "SELECT: TOGGLE");
}

// ===========================================================================
// GPS (2x)
// ===========================================================================

void drawPage_GPSHome() {
    drawHomeTemplate("GPS", "Position & satellites", ICON_GPS_PIN, 2);
}

void drawPage_GPSLatitude() {
    updateGPS();
    bool valid = isGPSValid();
    double lat = valid ? getLatitude() : 0;
    String val = valid ? String(fabs(lat), 4) : "--";
    const char *hemi = (valid && lat < 0) ? "S" : "N";
    drawValueTemplate("GPS", ICON_GPS_PIN, 1, 6, "LATITUDE", val, valid ? hemi : "", !valid);
}

void drawPage_GPSLongitude() {
    updateGPS();
    bool valid = isGPSValid();
    double lon = valid ? getLongitude() : 0;
    String val = valid ? String(fabs(lon), 4) : "--";
    const char *hemi = (valid && lon < 0) ? "W" : "E";
    drawValueTemplate("GPS", ICON_GPS_PIN, 2, 6, "LONGITUDE", val, valid ? hemi : "", !valid);
}

void drawPage_GPSSpeed() {
    updateGPS();
    bool valid = isGPSValid();
    double spd = valid ? getSpeed() : 0;
    String val = valid ? String(spd, 1) : "--";
    drawValueTemplate("GPS", ICON_SPEED, 3, 6, "SPEED", val, "km/h", !valid);
}

void drawPage_GPSAltitude() {
    updateGPS();
    bool valid = isGPSValid();
    double alt = valid ? getAltitude() : 0;
    String val = valid ? String(alt, 0) : "--";
    drawValueTemplate("GPS", ICON_MOUNTAIN, 4, 6, "ALTITUDE", val, "m", !valid);
}

void drawPage_GPSHDOP() {
    updateGPS();
    bool valid = isGPSValid();
    double hdop = valid ? getHDOP() : 0;
    String val = valid ? String(hdop, 1) : "--";
    drawValueTemplate("GPS", ICON_TARGET, 5, 6, "HDOP", val, "", !valid, "Lower value = better precision");
}

void drawPage_GPSSatellites() {
    updateGPS();
    bool valid = isGPSValid();
    uint32_t sats = getSatellites();
    String val = String((unsigned long)sats);
    drawValueTemplate("GPS", ICON_SATELLITE, 6, 6, "SATELLITES", val, "SATS", !valid && sats == 0,
                       valid ? "Fix acquired" : "Searching for fix...");
}

// ===========================================================================
// LORA (3x)
// ===========================================================================

void drawPage_LoRaHome() {
    drawHomeTemplate("LORA", "Long range messaging", ICON_ANTENNA, 3);
}

void drawPage_LoRaSendOK() {
    tft.fillScreen(UI_BG);
    drawHeader("LORA", ICON_ANTENNA);
    drawSubDots(1, 3);

    int W = tft.width();
    int H = tft.height();
    drawIcon(ICON_CHECK, W / 2, H / 2 - 16, 26, UI_ORANGE);

    tft.setTextFont(4);
    tft.setTextColor(UI_ORANGE, UI_BG);
    tft.setTextDatum(MC_DATUM);
    tft.drawString("SEND: OK", W / 2, H / 2 + 26);

    tft.setTextFont(2);
    tft.setTextColor(UI_TEXT, UI_BG);
    tft.drawString("Broadcast an all-clear status", W / 2, H / 2 + 46);

    drawFooterNav("<  BACK", "SELECT: SEND");
}

void drawPage_LoRaSendSOS() {
    tft.fillScreen(UI_BG);
    drawHeader("LORA", ICON_ANTENNA);
    drawSubDots(2, 3);

    int W = tft.width();
    int H = tft.height();
    drawIcon(ICON_WARNING, W / 2, H / 2 - 16, 26, UI_ORANGE);

    tft.setTextFont(4);
    tft.setTextColor(UI_WARN, UI_BG);
    tft.setTextDatum(MC_DATUM);
    tft.drawString("SEND: SOS", W / 2, H / 2 + 26);

    tft.setTextFont(2);
    tft.setTextColor(UI_TEXT, UI_BG);
    tft.drawString("Broadcast a distress signal", W / 2, H / 2 + 46);

    drawFooterNav("<  BACK", "SELECT: SEND");
}

void drawPage_LoRaSendGPS() {
    tft.fillScreen(UI_BG);
    drawHeader("LORA", ICON_ANTENNA);
    drawSubDots(3, 3);

    int W = tft.width();
    int H = tft.height();
    drawIcon(ICON_GPS_PIN, W / 2, H / 2 - 16, 26, UI_ORANGE);

    tft.setTextFont(4);
    tft.setTextColor(UI_ORANGE, UI_BG);
    tft.setTextDatum(MC_DATUM);
    tft.drawString("SEND: GPS", W / 2, H / 2 + 26);

    tft.setTextFont(2);
    tft.setTextColor(UI_TEXT, UI_BG);
    tft.drawString("Broadcast current position", W / 2, H / 2 + 46);

    drawFooterNav("<  BACK", "SELECT: SEND");
}

// ===========================================================================
// SURVIVAL TIPS (4x)
// ===========================================================================

void drawPage_TipsHome() {
    drawHomeTemplate("SURVIVAL TIPS", "Field guide & advice", ICON_BOOK, 4);
}

void drawPage_Tips(int tipIndex) {
    if (tipIndex < 0) tipIndex = 0;
    if (tipIndex > 4) tipIndex = 4;

    tft.fillScreen(UI_BG);
    drawHeader("SURVIVAL TIPS", ICON_BOOK);
    drawSubDots(tipIndex + 1, 5);

    int W = tft.width();
    int margin = 10;

    String question = String(questions[tipIndex].c_str());
    String answer = String(answers[tipIndex].c_str());

    int y = HEADER_H + 8;
    y = drawWrappedText(question, margin, y, W - margin * 2, 18, 4, UI_ORANGE);
    y += 4;
    drawWrappedText(answer, margin, y, W - margin * 2, 13, 2, UI_TEXT);

    drawFooterNav("<  BACK", "^ v  NEXT TIP");
}

// ===========================================================================
// DEVICE (5x)
// ===========================================================================

void drawPage_DeviceHome() {
    drawHomeTemplate("DEVICE", "Battery & hardware", ICON_BATTERY, 5);
}

void drawPage_DeviceBattery() {
    float voltage = getbattery();
    float pct = maxlipo.cellPercent();
    bool valid = !isnan(pct) && pct >= 0 && voltage > 0;
    String val = valid ? String((int)round(pct)) : "--";
    String sub = valid ? (String(voltage, 2) + " V") : "No battery detected";
    drawValueTemplate("DEVICE", ICON_BATTERY, 1, 3, "BATTERY", val, "%", !valid, sub.c_str());
}

void drawPage_DeviceBatteryLife() {
    float pct = maxlipo.cellPercent();
    bool valid = !isnan(pct) && pct >= 0;
    float hours = valid ? (pct / 100.0f) * ESTIMATED_FULL_RUNTIME_HOURS : 0;
    String val = valid ? String(hours, 1) : "--";
    drawValueTemplate("DEVICE", ICON_CLOCK, 2, 3, "EST. TIME LEFT", val, "h", !valid,
                       "Rough estimate, no current sensing");
}

void drawPage_DeviceHardware() {
    tft.fillScreen(UI_BG);
    drawHeader("DEVICE", ICON_CHIP);
    drawSubDots(3, 3);

    const char *lines[] = {
        "ESP32-S3",
        "ST7789 IPS 170x320",
        "BME280 - temp/humid/pressure",
        "MAX17048 - fuel gauge",
        "EBYTE E220 - LoRa radio",
        "u-blox - GPS module"
    };
    int count = sizeof(lines) / sizeof(lines[0]);

    int x = 16;
    int y = HEADER_H + 12;
    int lineHeight = 18;

    tft.setTextFont(2);
    tft.setTextDatum(ML_DATUM);
    for (int i = 0; i < count; i++) {
        tft.fillCircle(x, y + 5, 2, UI_ORANGE);
        tft.setTextColor(UI_TEXT, UI_BG);
        tft.drawString(lines[i], x + 10, y + 5);
        y += lineHeight;
    }

    drawFooterNav("<  BACK", "");
}

// ===========================================================================
// Dispatcher
// ===========================================================================

void drawUIPage(int current_page, bool flashlightOn) {
    switch (current_page) {
    case 0: drawPage_EnvironmentHome(); break;
    case 1: drawPage_EnvironmentTemperature(); break;
    case 2: drawPage_EnvironmentHumidity(); break;
    case 3: drawPage_EnvironmentPressure(); break;
    case 4: drawPage_EnvironmentAltitude(); break;

    case 10: drawPage_FlashlightHome(); break;
    case 11: drawPage_FlashlightToggle(flashlightOn); break;

    case 20: drawPage_GPSHome(); break;
    case 21: drawPage_GPSLatitude(); break;
    case 22: drawPage_GPSLongitude(); break;
    case 23: drawPage_GPSSpeed(); break;
    case 24: drawPage_GPSAltitude(); break;
    case 25: drawPage_GPSHDOP(); break;
    case 26: drawPage_GPSSatellites(); break;

    case 30: drawPage_LoRaHome(); break;
    case 31: drawPage_LoRaSendOK(); break;
    case 32: drawPage_LoRaSendSOS(); break;
    case 33: drawPage_LoRaSendGPS(); break;

    case 40: drawPage_TipsHome(); break;
    case 41: drawPage_Tips(0); break;
    case 42: drawPage_Tips(1); break;
    case 43: drawPage_Tips(2); break;
    case 44: drawPage_Tips(3); break;
    case 45: drawPage_Tips(4); break;

    case 50: drawPage_DeviceHome(); break;
    case 51: drawPage_DeviceBattery(); break;
    case 52: drawPage_DeviceBatteryLife(); break;
    case 53: drawPage_DeviceHardware(); break;

    default: drawPage_EnvironmentHome(); break;
    }
}
