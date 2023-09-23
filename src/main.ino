#include <WiFi.h>

#include "network.h"

Network network;

void setup() {
    Serial.begin(115200);

    while (!Serial)
        ;

    network.setup();
}

void loop() { network.loop(); }
