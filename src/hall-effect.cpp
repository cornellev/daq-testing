#include "hall-effect.h"

#include <Arduino.h>

#define INTERRUPT_PIN 15

HallEffect* instance;

void HallEffect::setup() {
    instance = this;
    auto callback = []() { instance->interrupt(); };
    attachInterrupt(INTERRUPT_PIN, callback, RISING);
}

void HallEffect::loop() {
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
}

void HallEffect::interrupt() { count++; }