#include <WiFi.h>

#include "network.h"

Network network;

#define INTERRUPT_PIN 15

unsigned long lastReading;
volatile int count = 0;

void interrupt() { count++; }

void setup() {
    Serial.begin(115200);

    while (!Serial)
        ;

    attachInterrupt(INTERRUPT_PIN, interrupt, RISING);
    network.setup();
}

void loop() {
    // print RPM values every 10 seconds
    unsigned long start = lastReading;
    unsigned long stop = millis();
    if (stop - start > 10000) {
        float rpm = (count * 60000.0) / (stop - start);
        Serial.print("RPM is ");
        Serial.println(rpm, 5);
        // reset variables
        count = 0;
        lastReading = stop;
    }

    network.loop();
}
