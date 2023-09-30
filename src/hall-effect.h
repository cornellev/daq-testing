#pragma once

class HallEffect {
   private:
    volatile int count;
    unsigned long lastReading;

    void interrupt();

   public:
    void setup();
    void loop();
};