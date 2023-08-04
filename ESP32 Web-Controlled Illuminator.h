#include <WiFi.h>
#include <WebServer.h>
#include <FastLED.h>

// Replace with your network credentials
const char* ssid     = "your_SSID";
const char* password = "your_PASSWORD";

WebServer server(80);

// Define LED pins and configuration
#define NUM_LEDS 1
#define DATA_PIN 40  // LED_DI_PIN
#define CLOCK_PIN 39 // LED_CI_PIN

CRGB leds[NUM_LEDS];

void setup() {
    Serial.begin(115200);
    FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN>(leds, NUM_LEDS);

    // Connect to Wi-Fi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");

    // Route to turn on LED
    server.on("/on", HTTP_GET, []() {
        leds[0] = CRGB::White; // You can change the color to your preference
        FastLED.show();
        server.send(200, "text/plain", "LED is ON");
    });

    // Route to turn off LED
    server.on("/off", HTTP_GET, []() {
        leds[0] = CRGB::Black;
        FastLED.show();
        server.send(200, "text/plain", "LED is OFF");
    });

    // Start server
    server.begin();
}

void loop() {
    server.handleClient();
}
