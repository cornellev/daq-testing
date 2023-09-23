#pragma once

#include <WebSocketsClient.h>
#include <WiFi.h>

class Network {
   private:
    unsigned long lastFastFlash, lastSlowFlash, lastWebRequest, lastPeriodPrint;
    WiFiClient client;

   public:
    void setup();
    void loop();
};