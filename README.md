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
| **Display** | 1.9" IPS Module ST7789 | SPI | Smooth UI with menus/submenus, PWM brightness control |
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
LICENSE
README.md
assets/                     # Logos & documentation images (PNG)
case/                       # 3D enclosure design files (if applicable)
firmware/                   # Main firmware codebase
├── platformio.ini          # PlatformIO project config
├── README.md
├── include/
│   ├── buttonread.h
│   ├── config.h
│   ├── flashlight.h
│   ├── getbattery.h
│   ├── gps.h
│   ├── navigation.h
│   ├── nomad_logo.h
│   ├── pins.h
│   ├── readtemperature.h
│   ├── tips.h
│   └── ui.h
├── lib/
│   └── README
├── src/
│   ├── buttonread.cpp
│   ├── flashlight.cpp
│   ├── getbattery.cpp
│   ├── gps.cpp
│   ├── main.cpp
│   ├── navigation.cpp
│   ├── readtemperature.cpp
│   ├── tips.cpp
│   └── ui.cpp
└── test/
	└── README
pcb/
├── ~nomad.kicad_pcb.lck
├── ~nomad.kicad_pro.lck
├── modules.kicad_sch
├── nomad.kicad_pcb
├── nomad.kicad_prl
├── nomad.kicad_pro
├── nomad.kicad_sch
└── nomad-backups/

```




## 📄 License

See [`LICENSE`](LICENSE) for project licensing details.

---

**Last Updated**: May 2026 | **Status**: Active Development