#include "network.h"

#include <WebSocketsClient.h>
#include <WiFi.h>

#define LED_PIN 13

void Network::setup() {
    const char* ssid = "jasooon";
    const char* password = "12345678";
    WiFi.begin(ssid, password);
    pinMode(LED_PIN, OUTPUT);
}

void Network::loop() {
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
            request();
        }
    }
}

void Network::request() {
    Serial.println("attempting request");
    uint8_t host_bytes[] = {172, 20, 10, 2};
    if (client.connect(host_bytes, 8080)) {
        Serial.println("connected");
        // This will send the request to the server
        client.println("GET / HTTP/1.1");
        client.print("Host: ");
        client.print("172.20.10.2");
        client.print(":");
        client.println(8080);
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
        Serial.println("failed to connect to client :(");
    }
    lastWebRequest = millis();
}

void hexdump(const void* mem, uint32_t len, uint8_t cols = 16) {
    const uint8_t* src = (const uint8_t*) mem;
    Serial.printf("\n[HEXDUMP] Address: 0x%08X len: 0x%X (%d)", (ptrdiff_t) src, len, len);
    for (uint32_t i = 0; i < len; i++) {
        if (i % cols == 0) {
            Serial.printf("\n[0x%08X] 0x%08X: ", (ptrdiff_t) src, i);
        }
        Serial.printf("%02X ", *src);
        src++;
    }
    Serial.printf("\n");
}

void Network::socket_event(WStype_t type, uint8_t* payload, size_t length) {
    switch (type) {
        case WStype_DISCONNECTED:
            Serial.printf("[WSc] Disconnected!\n");
            break;
        case WStype_CONNECTED:
            Serial.printf("[WSc] Connected to url: %s\n", payload);

            // send message to server when Connected
            socket.sendTXT("Connected");
            break;
        case WStype_TEXT:
            Serial.printf("[WSc] get text: %s\n", payload);

            // send message to server
            // webSocket.sendTXT("message here");
            break;
        case WStype_BIN:
            Serial.printf("[WSc] get binary length: %u\n", length);
            hexdump(payload, length);

            // send data to server
            // webSocket.sendBIN(payload, length);
            break;
        case WStype_ERROR:
        case WStype_FRAGMENT_TEXT_START:
        case WStype_FRAGMENT_BIN_START:
        case WStype_FRAGMENT:
        case WStype_FRAGMENT_FIN:
            break;
    }
}