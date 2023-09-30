#pragma once

class HallEffect {
   private:
    volatile int count;
    unsigned long lastReading;
    void (*callback)(float);

    void interrupt();

   public:
    void setup();
    void loop();
    void onData(void (*callback)(float));
};