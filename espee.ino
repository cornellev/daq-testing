#include <WiFi.h>

#define LED_PIN 13

// my phone hotspot password. please don't abuse this!
const char* ssid = "jasooon";
const char* password = "12345678";

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
    while (WiFi.status() != WL_CONNECTED) {
      digitalWrite(LED_PIN, HIGH);
      delay(100);
      digitalWrite(LED_PIN, LOW);
      delay(100);
    }

    Serial.print("IP is ");
    Serial.println(WiFi.localIP());
    Serial.println("banana!");
  
    digitalWrite(LED_PIN, HIGH);
    delay(1000);
    digitalWrite(LED_PIN, LOW);
    delay(1000);
}
