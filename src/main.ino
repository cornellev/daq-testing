#include <WiFi.h>

#define LED_PIN 13

const char* ssid = "jasooon";
const char* password = "12345678";

unsigned long lastFastFlash = 0;
unsigned long lastSlowFlash = 0;
unsigned long lastWebRequest = 0;

WiFiClient client;

void setup() {
    pinMode(LED_PIN, OUTPUT);
    Serial.begin(115200);

    while (!Serial)
        ;

    WiFi.begin(ssid, password);
}

void loop() {
    // flash fast when disconnected
    if (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
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
        else {
            Serial.print("IP address: ");
            Serial.println(WiFi.localIP());
            lastSlowFlash = millis();
        }

        // make internet requests every 5 seconds
        if (millis() - lastWebRequest > 5000) {
            Serial.println("attempting request");
            if (client.connect("example.com", 80)) {
                Serial.println("connected");
                // This will send the request to the server
                client.println("GET / HTTP/1.1");
                client.print("Host: ");
                client.print("example.com");
                client.print(":");
                client.println(80);
                client.println("Connection: close");
                client.println();

                unsigned long timeout = millis();
                while (client.available() == 0) {
                    if (millis() - timeout > 5000) {
                        Serial.println("client timed out");
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
            } else {
                Serial.println("get fucked boi");
            }
            lastWebRequest = millis();
        }
    }
}
