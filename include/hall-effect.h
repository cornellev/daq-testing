#pragma once

#include <stdint.h>

class HallEffect {
   private:
    volatile int count;
    unsigned long lastReading;
    void (*callback)(double);

    void interrupt();

   public:
    void setup(uint8_t interruptPin);
    void loop();
    void onData(void (*callback)(double));
};