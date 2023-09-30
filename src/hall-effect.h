#pragma once

class HallEffect {
   private:
    volatile int count;
    unsigned long lastReading;
    void (*callback)(double);

    void interrupt();

   public:
    void setup();
    void loop();
    void onData(void (*callback)(double));
};