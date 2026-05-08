# Nomad
## Outdoor Embedded Device for Exploration

![Nomad Logo](assets/nomadlogo.png)

---

## 📋 Project Overview

**Nomad** is a custom-designed outdoor mobile device built on the **ESP32-S3** microcontroller. Designed for explorers, researchers, and outdoor enthusiasts, Nomad combines GPS localization, LoRa communication, environmental sensing, and long battery life into a portable, rugged package.

### Key Features
- **GPS Navigation** with real-time positioning and waypoint tracking
- **LoRa Communication** for long-range mesh-style messaging (SOS alerts, coordinate sharing)
- **Environmental Monitoring** (temperature, atmospheric pressure, altitude)
- **Intuitive UI** with multi-level menus and state-machine-driven navigation
- **Battery Optimization** with deep sleep and intelligent power management
- **Custom PCB Design** 

---

## 🔧 Technical Architecture

### Core Components

| Component | Specification | Interface | Purpose |
|-----------|---------------|-----------|---------|
| **MCU** | ESP32-S3 | — | Main processor, development in C++/PlatformIO/Arduino |
| **Display** | LCD IPS Screen | SPI | Smooth UI with menus/submenus, PWM brightness control |
| **GPS** | u-blox M10 | UART | Localization; uses TinyGPS++ library |
| **LoRa** | Ebyte E22 | SPI | Long-range messaging (SOS, coordinates) |
| **Environmental** | BME280 | I2C | Temperature & atmospheric pressure sensing |
| **Input** | 5 Buttons + PCF8574 | I2C (GPIO Expander) | Robust button handling with interrupt support |
| **Power** | Li-ion 18650 | — | Main battery; needs protection circuit & optimization |

### Development Stack
- **Language**: C++
- **Framework**: Arduino (via PlatformIO)
- **Build System**: PlatformIO
- **IDE**: VS Code with PlatformIO extension

---

## 📁 Project Structure

```
Nomad/
├── firmware/                 # Main firmware codebase
│   ├── platformio.ini       # PlatformIO project config
│   ├── src/
│   │   ├── main.cpp         # Entry point, setup() and loop()
│   │   ├── gps.cpp          # GPS module driver (u-blox M10, NMEA)
│   │   ├── lora.cpp         # LoRa communication handler
│   │   ├── readtemperature.cpp # BME280 sensor interface
│   │   ├── buttonread.cpp   # Button input & PCF8574 handling
│   │   ├── flashlight.cpp   # GPIO/LED control
│   │   ├── navigation.cpp   # UI state machine & display logic
│   │   └── ...
│   ├── include/
│   │   ├── gps.h
│   │   ├── lora.h
│   │   ├── config.h         # Pinout, constants, configuration
│   │   ├── readtemperature.h
│   │   ├── buttonread.h
│   │   ├── navigation.h
│   │   └── ...
│   ├── lib/                 # Third-party libraries
│   └── test/                # Unit tests
├── pcb/                      # KiCad PCB design files
│   ├── nomad.kicad_sch      # Schematic
│   ├── nomad.kicad_pcb      # PCB layout
│   └── ...
├── assets/                   # Logos, documentation images
│   └── every logo in png format
├── case/                     # 3D enclosure design files (if applicable)
└── README.md                 # This file
```


---

## 📚 Key Libraries & Drivers

| Library | Purpose | Link/Notes |
|---------|---------|-----------|
| **TinyGPS++** | GPS NMEA parsing | Lightweight, handles u-blox M10 streams |
| **BME280** | Environmental sensor driver | I2C interface for temperature/pressure |
| **PCF8574** | GPIO expander | 8-bit I/O via I2C (buttons & interrupts) |
| **SPI/Wire** | Hardware protocols | Built-in Arduino/ESP32 libraries |
| **LoRa Ebyte E22** | LoRa module driver | Custom or community driver (SPI-based) |


## 📄 License

See [`LICENSE`](LICENSE) for project licensing details.

---

**Last Updated**: May 2026 | **Status**: Active Development