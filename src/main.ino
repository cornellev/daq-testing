#include <WiFi.h>

#include "network.h"

Network network;

#define INTERRUPT_PIN 15

volatile bool updated = false;
volatile int count = 0;

void interrupt() {
    count++;
    updated = true;
}

void setup() {
    Serial.begin(115200);

    while (!Serial)
        ;

    attachInterrupt(INTERRUPT_PIN, interrupt, RISING);
    network.setup();
}

void loop() {
    if (updated) {
        Serial.println(count);
        updated = false;
    }
    network.loop();
}
