# ESP32 IoT Smart Fire Alarm System

An ESP32-based smart fire alarm and smoke detection system with real-time alerts and IoT cloud monitoring.

---

## 🌟 Key Features

* **Real-time Fire & Smoke Detection:** Continuously monitors ambient temperature and gas/smoke concentration.
* **Instant Alerts:** Sends instant notifications via [Telegram Bot / Blynk / Email / SMS] when thresholds are exceeded.
* **Local Alarms:** Triggers an on-site buzzer and warning LED for immediate evacuation.
* **IoT Dashboard:** Live monitoring of sensor data via [Blynk / Adafruit IO / ThingsBoard / MQTT].
* **Fail-safe Operation:** Works offline for local alarm even if Wi-Fi connection is lost.

---

## 🛠️ Hardware Requirements

* **Microcontroller:** ESP32 Development Board
* **Sensors:**
  * Flame Sensor (IR Flame Detection)
  * MQ-2 / MQ-135 Gas Sensor (Smoke / Flammable Gas Detection)
  * DHT11 / DHT22 (Temperature & Humidity Sensor)
* **Outputs & Display:**
  * Active Buzzer (5V / 3.3V)
  * 16x2 / 20x4 I2C LCD Display (with PCF8574 adapter)
* **Others:** Breadboard, Jumper wires, 5V Micro-USB / Type-C Power Supply.

---

## 📌 Pinout / Wiring Diagram

| Component / Module | ESP32 GPIO Pin | Type / Interface | Description / Note |
| :--- | :--- | :--- | :--- |
| **Flame Sensor (DO)** | `GPIO 3` | Digital Input | Detects infrared flame radiation |
| **Gas Sensor (DO / AO)** | `GPIO 8` | Input | Detects gas leak / smoke density |
| **DHT Sensor (Data)** | `GPIO 9` | Digital I/O | Reads ambient temperature & humidity |
| **Active Buzzer (+)** | `GPIO 11` | Digital Output | Triggers audio alarm on emergency |
| **I2C LCD (SDA)** | `GPIO 4` | I2C Data | Data line for display |
| **I2C LCD (SCL)** | `GPIO 5` | I2C Clock | Clock line for display |
| **Power Supply** | `VCC / GND` | 5V / 3.3V & GND | Common power rail |

---

## 🚀 Getting Started

### 1. Prerequisites
* [Arduino IDE](https://www.arduino.cc/en/software) (or VS Code + PlatformIO)
* ESP32 Board Package installed on Arduino IDE
* Required Libraries:
  * `WiFi.h`
  * `DHT sensor library`
  * `Blynk` / `PubSubClient` (for MQTT)
  * `Adafruit_SSD1306` (if using OLED)

### 2. Configuration
Clone the repository and open the sketch:
```bash
git clone [https://github.com/workingdattran/esp32-iot-smart-fire-alarm.git](https://github.com/workingdattran/esp32-iot-smart-fire-alarm.git)
