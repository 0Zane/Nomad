# Nomad

**Outdoor embedded device for exploration**



[![ESP32-S3](https://img.shields.io/badge/MCU-ESP32--S3-2B6CB0?style=for-the-badge)](#technical-architecture)
[![PlatformIO](https://img.shields.io/badge/Build-PlatformIO-F5822A?style=for-the-badge)](#development-stack)
[![Arduino](https://img.shields.io/badge/Framework-Arduino-00979D?style=for-the-badge)](#development-stack)
[![LoRa](https://img.shields.io/badge/Radio-LoRa-5B3A91?style=for-the-badge)](#technical-architecture)

Nomad is a custom outdoor mobile device built around the **ESP32-S3**. It is designed for explorers, researchers, and outdoor enthusiasts who need reliable positioning, long-range communication, environmental awareness, and practical survival utilities in a compact rugged package.

> **Project status:** Active development  
> **Last updated:** June 2026

[![Nomad zine](https://raw.githubusercontent.com/0Zane/Nomad/341650ad904c9da342a7fef04f9b7398d65ead2c/assets/nomadzine.png)](https://github.com/0Zane/Nomad/blob/341650ad904c9da342a7fef04f9b7398d65ead2c/assets/nomadzine.png)

## Documentation

| Resource | Description |
| --- | --- |
| [Nomad Zine](https://github.com/0Zane/Nomad/blob/341650ad904c9da342a7fef04f9b7398d65ead2c/assets/nomadzine.png) | Visual project zine and product-style overview |
| [Bill of Materials](https://github.com/0Zane/Nomad/blob/main/pcb/bom.csv) | Complete component list with quantities and specifications |
| [Main Schematic](https://github.com/0Zane/Nomad/blob/1c8a336e28e47b4648a542668c6f2eea3e4071de/pcb/nomad.svg) | Full board schematic |
| [Module Schematic](https://github.com/0Zane/Nomad/blob/1c8a336e28e47b4648a542668c6f2eea3e4071de/pcb/modules.svg) | Supporting module schematic |

## Table of Contents

- [Project Overview](#project-overview)
- [Key Features](#key-features)
- [Technical Architecture](#technical-architecture)
- [Hardware Design](#hardware-design)
- [Bill of Materials](#bill-of-materials)
- [Firmware](#firmware)
- [Project Structure](#project-structure)
- [License](#license)

## Project Overview

Nomad combines navigation, messaging, sensing, power management, and a custom interface into one portable embedded system.

The device is built for field use, with an emphasis on:

- Knowing where you are through GPS positioning and waypoint tracking.
- Staying connected through long-range LoRa messaging.
- Understanding local conditions through environmental sensing.
- Conserving energy through deep sleep and power-aware firmware.
- Providing simple, fast interaction through buttons and a menu-driven UI.

## Key Features

| Feature | What it enables |
| --- | --- |
| **GPS navigation** | Real-time position, coordinates, and waypoint-oriented navigation |
| **LoRa communication** | Long-range SOS alerts, coordinate sharing, and lightweight messages |
| **Environmental monitoring** | Temperature, pressure, and altitude-related readings |
| **Menu-driven UI** | Multi-level navigation built around a clear state-machine structure |
| **Survival tips** | Practical outdoor guidance available directly on the device |
| **Battery optimization** | Deep sleep and intelligent power-management behavior |
| **Custom PCB** | Purpose-built hardware layout for the full Nomad system |
| **Rugged enclosure** | 3D-designed case for portable outdoor use |

## Technical Architecture

### Core Components

| Component | Specification | Interface | Purpose |
| --- | --- | --- | --- |
| **MCU** | ESP32-S3-WROOM-1U | GPIO, UART, SPI, I2C | Main processor running C++ firmware with PlatformIO and Arduino |
| **Display** | 1.9 in IPS ST7789 display panel via FPC | SPI | Smooth UI rendering with menu/submenu screens and PWM brightness control |
| **GPS** | u-blox NEO-M8M | UART | High-precision localization using the TinyGPS++ library |
| **LoRa** | Ebyte E220-900T22S | UART | Long-range messaging for SOS, coordinate sharing, and text packets |
| **Environmental sensor** | BME280 | I2C | Temperature and atmospheric pressure sensing |
| **Input** | 5 buttons with PCF8574T GPIO expander | I2C | Robust button handling with interrupt support |
| **Fuel gauge** | MAX17048G_T10 | I2C | Battery voltage and state-of-charge monitoring |
| **Charger IC** | MCP73831-2-OT | Power management | Li-Po battery charging management |
| **Buck-boost converter** | TPS63060 | Power management | Stable regulated power delivery |
| **Flashlight** | LED | GPIO pin 1 | Controlled illumination for field use |
| **Power source** | Protected Li-ion battery | Power | Main battery with integrated protection circuit |

### Development Stack

| Layer | Tooling |
| --- | --- |
| **Language** | C++ |
| **Framework** | Arduino |
| **Build system** | PlatformIO |
| **IDE** | VS Code with the PlatformIO extension |
| **Primary firmware target** | ESP32-S3 |

## Hardware Design

### Main Schematic

[![Nomad main schematic](https://raw.githubusercontent.com/0Zane/Nomad/1c8a336e28e47b4648a542668c6f2eea3e4071de/pcb/nomad.svg)](https://github.com/0Zane/Nomad/blob/1c8a336e28e47b4648a542668c6f2eea3e4071de/pcb/nomad.svg)

### Module Schematic

[![Nomad module schematic](https://raw.githubusercontent.com/0Zane/Nomad/1c8a336e28e47b4648a542668c6f2eea3e4071de/pcb/modules.svg)](https://github.com/0Zane/Nomad/blob/1c8a336e28e47b4648a542668c6f2eea3e4071de/pcb/modules.svg)

### 3D Case

[![Nomad case](https://raw.githubusercontent.com/0Zane/Nomad/361d461af25cd4167b1612e461230889cdf5da81/case/case.png)](https://github.com/0Zane/Nomad/blob/361d461af25cd4167b1612e461230889cdf5da81/case/case.png)

