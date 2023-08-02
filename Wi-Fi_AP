#include <WiFi.h>

const char* ssids[] = {
  "NeverGonnaGiveYouUp",
  "NeverGonnaLetYouDown",
  "NeverGonnaRunAround",
  "AndDesertYou"
};
const char* passwords[] = {
  "password123",
  "password456",
  "password123",
  "password456"
};
const int numAPs = 4;
int currentAP = 0;

unsigned long lastChange = 0;
const int interval = 10000;  // Switch every 10 seconds

void setup() {
  Serial.begin(115200);
  setupAP();
}

void loop() {
  if (millis() - lastChange > interval) {
    currentAP = (currentAP + 1) % numAPs;  // Switch to the next AP
    setupAP();
    lastChange = millis();
  }
}

void setupAP() {
  WiFi.mode(WIFI_MODE_AP);
  WiFi.softAP(ssids[currentAP], passwords[currentAP]);

  Serial.println("Access Point Started");
  Serial.print("SSID: ");
  Serial.println(ssids[currentAP]);
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());
}
