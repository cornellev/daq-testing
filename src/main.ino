#include <WiFi.h>

#include "hall-effect.h"
#include "network.h"

Network network;
HallEffect halleffect;

void setup() {
    Serial.begin(115200);

    while (!Serial)
        ;

    network.setup();
    halleffect.setup();
}

void loop() {
    network.loop();
    halleffect.loop();
}
