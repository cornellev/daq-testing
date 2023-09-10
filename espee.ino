#include <WiFi.h>

#define LED_PIN 13

// my phone hotspot password. please don't abuse this!
const char* ssid = "jasooon";
const char* password = "12345678";

unsigned long lastFastFlash = 0;
unsigned long lastSlowFlash = 0;

bool connected = false;

void setup() {
    pinMode(LED_PIN, OUTPUT);
    Serial.begin(115200);

    // connect to hotspot
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
}

void loop() {
    // flash fast when disconnected
    if (WiFi.status() != WL_CONNECTED) {
        unsigned long elapsed = millis() - lastFastFlash;
        if (elapsed < 100)
            digitalWrite(LED_PIN, HIGH);
        else if (elapsed < 200)
            digitalWrite(LED_PIN, LOW);
        else
            lastFastFlash = millis();
    }

    else {
        // flash slow when connected
        unsigned long elapsed = millis() - lastSlowFlash;
        if (elapsed < 1000)
            digitalWrite(LED_PIN, HIGH);
        else if (elapsed < 2000)
            digitalWrite(LED_PIN, LOW);
        else
            lastSlowFlash = millis();
    }
}
