#include <WiFi.h>

#include "constants.h"
#include "hall-effect.h"
#include "network.h"

Network network;
HallEffect leftrpm;
HallEffect rightrpm;

void setup() {
    Serial.begin(115200);

    while (!Serial)
        ;

    network.setup();
    leftrpm.setup(constants::RPM::LEFT);
    rightrpm.setup(constants::RPM::RIGHT);

    leftrpm.onData([](double rpm) {
        if (network.send(rpm, constants::RPM::LEFT)) {
            Serial.print("LEFT RPM is ");
            Serial.println(rpm, 5);
        }
    });

    rightrpm.onData([](double rpm) {
        if (network.send(rpm, constants::RPM::RIGHT)) {
            Serial.print("RIGHT RPM is ");
            Serial.println(rpm, 5);
        }
    });
}

void loop() {
    network.loop();
    leftrpm.loop();
    rightrpm.loop();
}
