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

    halleffect.onData([](double rpm) {
        if (network.send(rpm)) {
            Serial.print("RPM is ");
            Serial.println(rpm, 5);
        }
    });
}

void loop() {
    network.loop();
    halleffect.loop();
}
