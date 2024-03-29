#include "network.h"

#include <WebSocketsClient.h>
#include <WiFi.h>

#include "constants.h"

WebSocketsClient socket;

void socket_event(WStype_t type, uint8_t* payload, size_t length);

void Network::setup() {
    WiFi.begin(constants::WIFI_SSID, constants::WIFI_PASSWORD);
    pinMode(LED_BUILTIN, OUTPUT);
    socket.begin(IPAddress(constants::HOST_IP), constants::HOST_PORT);

    socket.onEvent(socket_event);
    socket.setReconnectInterval(constants::RECONNECT_INTERVAL);
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
            digitalWrite(LED_BUILTIN, HIGH);
        else if (elapsed < 200)
            digitalWrite(LED_BUILTIN, LOW);
        else
            lastFastFlash = millis();
    }

    else {
        // flash slow when connected
        unsigned long elapsed = millis() - lastSlowFlash;
        if (elapsed < 1000)
            digitalWrite(LED_BUILTIN, HIGH);
        else if (elapsed < 2000)
            digitalWrite(LED_BUILTIN, LOW);
        else {
            lastSlowFlash = millis();
        }
    }
}

// returns whether the data was sent successfully
bool Network::send(double value, constants::RPM side) {
    std::string message = (side == constants::RPM::LEFT) ? "LEFT " : "RIGHT ";
    message += std::to_string(value);
    return socket.sendTXT(message.c_str());
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
