#include <Arduino.h>

#include "hall-effect.h"
#include "network.h"

void setup() {
    //  hall_setup();
    Serial.begin(115200);
    while (!Serial)
        ;
    Serial.println("banana");
    network_setup();
}

void loop() {
    // hall_loop();
    network_loop();
}