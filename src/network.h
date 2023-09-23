#pragma once

#include <WebSocketsClient.h>
#include <WiFi.h>

class Network {
   private:
    unsigned long lastFastFlash, lastSlowFlash, lastWebRequest, lastPeriodPrint;
    WiFiClient client;

    void request();
    // void socket_event(WStype_t type, uint8_t* payload, size_t length);

   public:
    void setup();
    void loop();
};