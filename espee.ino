#include <WiFi.h>

#define LED_PIN 13

// my phone hotspot password. please don't abuse this!
const char* ssid = "jasooon";
const char* password = "12345678";

unsigned long lastFastFlash = 0;
unsigned long lastSlowFlash = 0;
unsigned long lastWebRequest = 0;

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

        // make internet requests every 5 seconds
        if (millis() - lastWebRequest > 5000) {
            Serial.println("attempting request");
            request("example.com", 80);
//            WiFiClient client;
//            if (client.connect("reqbin.com", 80)) {
//              client.println("GET /echo HTTP/1.1");
//              client.println("Host: reqbin.com");
//              client.println("Connection: close");
//              client.println();
//            } else {
//              Serial.println("connection failed");
//            }
//
//            while (client.available()) {
//              char c = client.read();
//              Serial.print(c);
//            }
//
//            if (!client.connected()) {
//              client.stop();
//            }
          
//            HttpClient http;
//            http.begin("http://10.48.153.96:8080/");
//            int response = http.GET();
//            Serial.println(response);
//            Serial.println(http.getString());
//            http.end();

            lastWebRequest = millis();
        }
    }
}

void request(const char* host, uint8_t port) {
    Serial.print("connecting to domain: ");
    Serial.println(host);

    WiFiClient client;
    if (!client.connect(host, port)) {
        Serial.println("connection failed");
        return;
    }

    // This will send the request to the server
  client.print((String)"GET / HTTP/1.1\r\n" +
               "Host: " + String(host) + "\r\n" +
               "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
      if (millis() - timeout > 5000) {
          Serial.println(">>> Client Timeout !");
          client.stop();
          return;
      }
  }

  // Read all the lines of the reply from server and print them to Serial
  while (client.available()) {
      String line = client.readStringUntil('\r');
      Serial.print(line);
  }

  Serial.println();
  client.stop();
}
