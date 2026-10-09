[![Github issues](https://img.shields.io/github/issues/aadesh0706/IOT-ESP32-Evil-Twin-WiFi-Hacking-Deauthentication-Captive-Portal)](https://github.com/aadesh0706/IOT-ESP32-Evil-Twin-WiFi-Hacking-Deauthentication-Captive-Portal/issues)
[![Github forks](https://img.shields.io/github/forks/aadesh0706/IOT-ESP32-Evil-Twin-WiFi-Hacking-Deauthentication-Captive-Portal)](https://github.com/aadesh0706/IOT-ESP32-Evil-Twin-WiFi-Hacking-Deauthentication-Captive-Portal/network/members)
[![Github stars](https://img.shields.io/github/stars/aadesh0706/IOT-ESP32-Evil-Twin-WiFi-Hacking-Deauthentication-Captive-Portal)](https://github.com/aadesh0706/IOT-ESP32-Evil-Twin-WiFi-Hacking-Deauthentication-Captive-Portal/stargazers)
[![Top language](https://img.shields.io/github/languages/top/aadesh0706/IOT-ESP32-Evil-Twin-WiFi-Hacking-Deauthentication-Captive-Portal)](https://github.com/aadesh0706/IOT-ESP32-Evil-Twin-WiFi-Hacking-Deauthentication-Captive-Portal)

---

## 🧠 Tags

`ESP32` `IoT` `WiFi Hacking` `Deauthentication` `Captive Portal` `Microcontroller Security` `Arduino`

---

---

# 🚨 ESP32 Evil Twin WiFi Hacking | Deauthentication & Captive Portal 🚨

> **Disclaimer:** This project is for **educational purposes only**. Use it responsibly and legally. Unauthorized attacks on networks are illegal in most countries. 🌐🔒

---

![Profile Views](https://komarev.com/ghpvc/?username=aadesh0706&color=blue)  

---

### 🎥 **Demo Video**

Check out the demo of this project in action! 🎬  

---

### 🎯 **Project Overview**

This repository demonstrates how to execute an **Evil Twin WiFi Hacking** attack using an **ESP32** module. The attack forces users off their legitimate network by sending **deauthentication packets** and lures them into connecting to a fake access point where a **captive portal** captures their WiFi credentials. 

The project leverages **HTML**, **CSS**, and **JavaScript** to build a custom front-end for the captive portal, making it look like a legitimate login page.

---

## 🚀 **Features**
- 🛑 **Deauthentication Attack**: Disconnects devices from their current WiFi network.
- 🌐 **Captive Portal**: A fake login page where users unknowingly enter their WiFi credentials.
- 🎨 **Custom Frontend**: Built using **HTML**, **CSS**, and **JavaScript** for user interaction.
- 📡 **ESP32 Integration**: WiFi hacking on a powerful yet affordable ESP32 module.

---

## 🛠️ **Setup and Installation**

### 2️⃣ **Install Required Libraries**

Make sure you have the necessary libraries and tools installed to program the ESP32:

- **ESP32 Core for Arduino**: [Install Guide](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html)

### 3️⃣ **Upload the Code to ESP32**
1. Open the `esp32_deauth_attack.ino` file in your Arduino IDE.
2. Connect your ESP32 to your computer via USB.
3. Select your ESP32 board from the Tools > Board menu.
4. Click **Upload**.

### 4️⃣ **Customize the Captive Portal**
- The captive portal files are located in the `html/` folder. 🎨
- You can easily edit the design using **HTML**, **CSS**, and **JavaScript** to match your desired look and feel.

---

## ⚡ **How to Run the Attack**

1. **Launch the Deauthentication Attack**: 📶 Force devices off the legitimate WiFi network.
2. **Start the Fake AP**: 🖧 Broadcast your rogue access point.
3. **Use the Captive Portal**: 🌐 When users attempt to reconnect, they are directed to a fake login page.
4. **Capture WiFi Credentials**: 🔐 Credentials entered by users are logged on the ESP32.

---

## 📂 **Files Included**
- `esp32_deauth_attack.ino`: The main code for the deauthentication attack.
- `html/`: Contains all the files for the captive portal (HTML, CSS, JavaScript).
- `README.md`: Overview, setup instructions, and usage information.

---

## 🔗 **How It Works**

1. **Deauthentication Attack**: The ESP32 sends deauth packets to disconnect devices from their original network.
2. **Rogue Access Point**: After being disconnected, the ESP32 broadcasts a rogue AP with a similar name (SSID) to the legitimate one.
3. **Captive Portal**: When users attempt to connect to the rogue AP, they are redirected to a fake login page asking for WiFi credentials.
4. **Credentials Logged**: Any credentials entered are captured and stored on the ESP32.

---

## 💻 **Technologies Used**
- **ESP32**: Low-cost WiFi module.
- **HTML**: Structure for the captive portal.
- **CSS**: Styling for a user-friendly portal interface.
- **JavaScript**: Handles user interactions and form submissions.

---

## 🚧 **Future Improvements**
- 🔒 Add encryption to securely transmit credentials.
- 📊 Create a log file to store captured credentials.
- 🔧 Improve the accuracy of deauthentication attacks.

---

## 👨‍💻 **Contributing**

Want to improve this project? Feel free to fork the repository, make changes, and submit a pull request. Contributions are always welcome! 🛠️

---

## 📝 **License**

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details. 📜

---

## ⚠️ **Disclaimer**

This project is intended for **educational and ethical testing purposes** only. **Do not** use this code to target any WiFi network without explicit permission from the network owner. Always comply with local laws and regulations.

---

### 📦 **Repository Tags**
```
ESP32, Evil Twin, WiFi Hacking, Deauthentication, Captive Portal, HTML, CSS, JavaScript, Cybersecurity, Ethical Hacking, ESP32 WiFi, IoT, WiFi Pentesting
```

---
