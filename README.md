# IOT-AIR-QUALITY-MONITOR
*COMPANY* : CODTECH IT SOLUTIONS
*NAME* : TANMOY NASKAR
INTERN ID : CT04DR1389
*DOMAIN* : INTERNET OF THINGS
*DURATION* : 4 WEEKS
*MENTOR* : NEELA SANTOSH

# Cloud-Connected Air Quality Monitor

![Project Status](https://img.shields.io/badge/Status-Prototype-yellow)
![Platform](https://img.shields.io/badge/Platform-ESP32-blue)
![Dashboard](https://img.shields.io/badge/Dashboard-ThingSpeak-red)

**AirAware** is an IoT environmental station that digitizes invisible air pollutants. It monitors Particulate Matter (PM2.5) and Carbon Dioxide (CO2) levels in real-time, displays them on a local OLED screen, and logs historical data to the ThingSpeak cloud for trend analysis.

## 🌟 Key Features
* **Dual Sensing:** Simultaneously reads laser dust data (PM2.5) and NDIR CO2 data.
* **Cloud Logging:** Uploads data to ThingSpeak every 20 seconds via REST API.
* **Local Display:** 0.96" OLED screen for immediate feedback.
* **Health Indicators:** (Planned) LED warning lights for "Unhealthy" air levels.

## 🧰 Tech Stack
* **Microcontroller:** ESP32 DevKit V1
* **Sensors:** PMS5003 (Dust), MH-Z19B (CO2)
* **Display:** SSD1306 OLED (I2C)
* **Cloud:** ThingSpeak API
* **Language:** C++ (Arduino)

## 🔌 Wiring Guide

| Component | ESP32 Pin |
| :--- | :--- |
| **MH-Z19B (TX/RX)** | GPIO 18 / 19 |
| **PMS5003 (TX/RX)** | GPIO 16 / 17 |
| **OLED (SDA/SCL)** | GPIO 21 / 22 |

## ⚙️ How to Run

1.  **Library Installation:**
    * `Adafruit_SSD1306` & `Adafruit_GFX`
    * `MH-Z19` (WifWaf version)
    * `Adafruit PM25AQI`
2.  **Cloud Setup:**
    * Create a Channel on [ThingSpeak](https://thingspeak.com).
    * Enable **Field 1** (PM2.5) and **Field 2** (CO2).
    * Copy the **Write API Key**.
3.  **Code Configuration:**
    * Paste your Wi-Fi credentials and API Key into the `config` section of the code.
    * Upload and open Serial Monitor to verify connection.

## 🧪 Simulation
You can test the logic of this project without hardware using the Wokwi Simulator.
[Link to Wokwi Simulation](https://wokwi.com/projects/YOUR_PROJECT_LINK_HERE)

## 🤝 Contributing
Contributions are welcome! Please open an issue or pull request for suggestions on better sensor calibration or power management.
