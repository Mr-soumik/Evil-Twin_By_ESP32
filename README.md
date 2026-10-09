## 📶 ESP32 Evil Twin + Deauther — WiFi Pentest Tool

A WiFi security testing and research tool for the **ESP32**, combining an **Evil Twin / Captive Portal demonstration** with WiFi deauthentication testing.

> ⚠️ **Disclaimer:** This project is intended strictly for authorized penetration testing, security research, and educational purposes. Only test networks and devices that you own or have explicit permission to test. Unauthorized credential collection or WiFi disruption may be illegal.

---

## 🧠 What Does It Do?

This project demonstrates common WiFi security concepts using an ESP32.

The tool provides a web-based interface for performing authorized wireless security tests.

### The tool can:

- 📡 Scan nearby WiFi networks
- 📋 Display SSID, BSSID, and channel information
- 🎯 Select a network for authorized testing
- 🪤 Create a captive-portal demonstration
- 🌐 Host a local web interface
- 💀 Demonstrate WiFi deauthentication/disassociation
- 🖥️ Control the ESP32 through a browser
- 📊 Display test status and runtime information

---

## ✨ Features

### 📡 WiFi Network Scanner

Scans nearby wireless networks and displays:

- SSID
- BSSID
- Channel
- Signal information

---

### 🎯 Target Selection

The web control panel allows you to select a network from the available scan results for authorized security testing.

---

### 🪤 Evil Twin / Captive Portal

Creates a rogue access point for demonstrating the security risks associated with:

- Fake WiFi networks
- Rogue access points
- Captive portals
- Social engineering
- Credential phishing

> Use this feature only in an isolated lab or on a network where you have explicit permission to test.

---

### 💀 Deauthentication Testing

Includes WiFi deauthentication/disassociation testing functionality.

This can be used in an authorized lab to study:

- WiFi management frames
- Client reconnection behavior
- Wireless network resilience
- Protected Management Frames (PMF)
- Wireless intrusion detection

> ⚠️ Deauthentication testing can disrupt WiFi connectivity. Never use it against networks or devices without authorization.

---

### 🖥️ Web-Based Control Panel

The ESP32 provides a browser-based control panel for managing the security-testing features.

The panel can be used for:

- Network scanning
- Target selection
- Captive-portal demonstration
- Test controls
- Status monitoring

---

### ⚡ ESP32 Optimized

Designed specifically for ESP32 hardware.

Promiscuous-mode functionality is enabled only when required by the testing workflow.

---

## 🧰 Hardware Requirements

| Component | Requirement |
|---|---|
| MCU | ESP32 |
| Compatible Boards | ESP32-WROOM / ESP32 DevKit / NodeMCU-32S |
| Power | USB / 5V supply |
| Programming | Arduino IDE |
| Connection | USB cable |

> ⚠️ **ESP32 only:** This project is designed for the ESP32 Arduino core and is not directly compatible with ESP8266.

---

## 📦 Software & Dependencies

### Required Libraries

The project uses the following libraries:

- `WiFi.h`
- `WebServer.h`
- `DNSServer.h`
- `esp_wifi.h`

`WiFi.h`, `WebServer.h`, and `DNSServer.h` are provided through the ESP32 Arduino core.

---

## ⚙️ ESP32 Board Setup

### 1. Open Arduino IDE

Open:

**File → Preferences**

### 2. Add ESP32 Board Manager URL

Add the following URL to **Additional Boards Manager URLs**:

```text
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json- Select a target network for security testing
- Create a rogue access point for captive-portal demonstrations
- Serve a simulated router-update login page
- Test submitted credentials against the authorized target network
- Perform WiFi deauthentication/disassociation testing
- Provide a browser-based control panel

---

✨ Features

📡 WiFi Network Scanner

Scans nearby wireless networks and displays:

- SSID
- BSSID
- WiFi Channel
- Available target networks

🎯 Target Selection

Select a network from the scan results through the web-based control panel.

🪤 Evil Twin / Captive Portal

Creates a test access point that can imitate the appearance of a selected WiFi network and serves a captive-portal page.

This feature is intended for demonstrating phishing and captive-portal security risks in an authorized lab environment.

💀 Deauthentication Testing

Includes WiFi deauthentication/disassociation functionality for authorized wireless security testing.

«Use this feature only on networks where you have explicit permission to perform disruption testing.»

🖥️ Web-Based Control Panel

Control the ESP32 directly from a browser.

The panel provides functionality for:

- WiFi scanning
- Target selection
- Captive portal control
- Security-testing controls
- Test status and logs

⚡ ESP32 Optimized

The project is designed specifically for the ESP32 and uses promiscuous mode only when required.

---

🧰 Hardware Requirements

Component| Requirement
MCU| ESP32
Compatible Boards| ESP32-WROOM / DevKit / NodeMCU-32S
Power| USB / 5V supply
Programming| Arduino IDE
Connection| USB cable

«⚠️ Important: This project is designed for ESP32. The original ESP8266 version is not directly compatible with ESP32.»

---

📦 Software & Dependencies

Required Libraries

The following libraries are required:

- "WiFi.h"
- "WebServer.h"
- "DNSServer.h"
- "esp_wifi.h"

The first three are included with the ESP32 Arduino core.

---

⚙️ ESP32 Board Setup

1. Open Arduino IDE

Open:

File → Preferences

2. Add ESP32 Board Manager URL

Add the following URL to Additional Boards Manager URLs:

"https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json"

3. Install ESP32 Board Package

Go to:

Tools → Board → Boards Manager

Search for:

esp32

Install the ESP32 board package provided by Espressif.

4. Select Your Board

Go to:

Tools → Board

Select the appropriate ESP32 board.

Then select the correct:

Tools → Port

---

🔌 How to Flash

1. Clone or download this repository.
2. Open the ".ino" file in Arduino IDE.
3. Make sure the required ESP32 board package is installed.
4. Select your ESP32 board.
5. Select the correct COM/USB port.
6. Connect the ESP32 to your computer.
7. Click Upload.
8. Open Serial Monitor.
9. Set the baud rate to:

"115200"

---

🕹️ Usage

After powering on, the ESP32 starts its configuration access point.

Default Access Point

Setting| Value
SSID| "M1z23R"
Password| "deauther"
Control Panel| "http://192.168.4.1"

Connect your phone or computer to the ESP32 access point and open the control-panel address in a browser.

---

🔍 Workflow

The general workflow is:

ESP32
  │
  ▼
Start Configuration AP
  │
  ▼
Open Web Control Panel
  │
  ▼
Scan Nearby Networks
  │
  ▼
Select Authorized Test Network
  │
  ├──► Captive Portal Demonstration
  │
  └──► Deauthentication Testing

---

📡 Network Scanning

The scanner periodically checks for nearby WiFi networks.

The scan results contain information such as:

SSID
BSSID
Channel

The control panel can then be used to select a network for authorized testing.

---

🪤 Captive Portal Demonstration

When the captive-portal test is enabled, the ESP32 creates a test access point and redirects connected clients to a simulated router-update page.

This demonstrates how attackers can use:

- Rogue access points
- Captive portals
- Fake login pages
- Social engineering

to attempt to obtain WiFi credentials.

«Security Note: Do not use this against networks or users without explicit authorization.»

---

💀 Deauthentication Testing

The project also demonstrates WiFi client disconnection through deauthentication/disassociation frames.

This can be useful for studying:

- WiFi management-frame security
- Client reconnection behavior
- Wireless intrusion detection
- Protected Management Frames (802.11w / PMF)
- Network resilience

«⚠️ Deauthentication can intentionally disrupt wireless connectivity. Perform these tests only in an isolated lab or on networks you are authorized to test.»

---

🖥️ Serial Monitor

The Serial Monitor can be used to observe the ESP32's runtime status.

Example status messages may include:

GOOD → WiFi connected
BAD  → WiFi connection failed

Other runtime information can also be displayed during scanning and testing.

---

🔐 Security & Privacy

This project demonstrates why users and network administrators should be aware of rogue access points and captive-portal attacks.

Recommended protections include:

- Use WPA2/WPA3 security
- Avoid entering passwords into unknown captive portals
- Verify the SSID and network before connecting
- Enable Protected Management Frames (PMF) where supported
- Use strong, unique WiFi passwords
- Monitor networks for rogue access points
- Use enterprise authentication where appropriate

---

⚠️ Legal Disclaimer

This project is provided for educational and authorized security-testing purposes only.

The developer is not responsible for misuse of this software.

You are responsible for ensuring that your use of this project complies with all applicable laws, regulations, and network policies.

Never use this tool to:

- Attack networks without permission
- Capture other people's credentials
- Disrupt public or private WiFi networks
- Intercept communications
- Perform unauthorized penetration testing

---

🛠️ Troubleshooting

ESP32 is not detected

- Check the USB cable.
- Install the appropriate USB-to-serial driver if required.
- Try another USB port.
- Verify the selected COM port.

Upload fails

- Verify the correct ESP32 board is selected.
- Close applications using the serial port.
- Press the BOOT button during upload if required by your board.
- Try a different USB cable.

Control panel does not open

Make sure your phone/computer is connected to:

M1z23R

Then open:

http://192.168.4.1

---

📚 Learning Topics

This project can be used to study:

- ESP32 WiFi programming
- 802.11 management frames
- WiFi security
- Rogue Access Points
- Captive Portals
- Wireless penetration testing
- Network authentication
- Protected Management Frames
- IoT security
- Embedded web servers

---

⭐ Project Status

Status: Experimental / Educational

This project is intended for laboratory testing and security research.

---

👨‍💻 Author

Harsh

If you find this project useful for learning about WiFi security, consider giving the repository a ⭐.
