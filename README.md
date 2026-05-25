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
- **Survival tips** useful tips for adventurers
- **Battery Optimization** with deep sleep and intelligent power management
- **Custom PCB Design** 

---

## 🔧 Technical Architecture

### Core Components

| Component | Specification | Interface | Purpose |
|-----------|---------------|-----------|---------|
| **MCU** | ESP32-S3-WROOM-1U | — | Main processor, development in C++/PlatformIO/Arduino |
| **Display** | LCD IPS Screen | SPI | Smooth UI with menus/submenus, PWM brightness control |
| **GPS** | u-blox M8N | UART | Localization; uses TinyGPS++ library |
| **LoRa** | Ebyte E22 | UART | Long-range messaging (SOS, coordinates) |
| **Environmental** | BME280 | I2C | Temperature & atmospheric pressure sensing |
| **Input** | 5 Buttons + PCF8574 | I2C (GPIO Expander) | Robust button handling with interrupt support |
| **Battery Manager** | Adafruit MAX17048 | I2C | Fuel gauge & battery voltage monitoring |
| **Flashlight** | LED | GPIO (Pin 1) | Controlled illumination light |
| **Power** | Li-ion | — | Main battery; needs protection circuit & optimization |

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
│   ├── nomad.kicad_sch      # Main system schematic
│   ├── modules.kicad_sch    # Modules schematic
│   ├── nomad.kicad_pcb      # PCB layout
│   └── ...
├── assets/                   # Logos, documentation images
│   └── every logo & graphics in png format
├── case/                     # 3D enclosure design files (if applicable)
└── README.md                 # This file
```




## 📄 License

See [`LICENSE`](LICENSE) for project licensing details.

---

**Last Updated**: May 2026 | **Status**: Active Development