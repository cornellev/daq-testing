#include "network.h"

#include <WebSocketsClient.h>
#include <WiFi.h>

#define LED_PIN 13

WebSocketsClient socket;

void socket_event(WStype_t type, uint8_t* payload, size_t length);

void Network::setup() {
    const char* ssid = "jasooon";
    const char* password = "12345678";
    WiFi.begin(ssid, password);
    pinMode(LED_PIN, OUTPUT);

    // always the same when hosting on iOS hotspot
    uint8_t host_bytes[] = {172, 20, 10, 2};
    // assumes that the WebSocket server is running on port 8080
    socket.begin(IPAddress(host_bytes), 8080);

    socket.onEvent(socket_event);
    socket.setReconnectInterval(5000);
}

void Network::loop() {
    socket.loop();

    // flash fast when disconnected
    if (WiFi.status() != WL_CONNECTED) {
        if (millis() - lastPeriodPrint > 500) {
            Serial.print(".");
            lastPeriodPrint = millis();
        }

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
            lastSlowFlash = millis();
        }

        // make internet requests every 5 seconds
        if (millis() - lastWebRequest > 5000) {
            // TODO this generate fake data for now
            float data = ((float) random()) / 65536;
            socket.sendTXT(String(data).c_str());
            lastWebRequest = millis();
        }
    }
}

void socket_event(WStype_t type, uint8_t* payload, size_t length) {
    switch (type) {
        case WStype_CONNECTED:
            Serial.println("WebSocket connected! :)");
            socket.sendTXT("hewwo i am espeeeee");
            break;

        case WStype_DISCONNECTED:
            Serial.println("WebSocket disconnected :(");
            break;

        case WStype_TEXT:
            // this happens if the server socket sends a string
            Serial.print("> ");
            Serial.printf("%s\n", payload);
            break;
    }
}
