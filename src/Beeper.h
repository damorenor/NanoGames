#pragma once

#include <Adafruit_SSD1306.h>
#include <Arduino.h>

class Beeper{
  private:
    int pinBeeper;
  public:
    Beeper(int pinBeeper);
    void setup();
    void soundStart();
    void soundPoint();
    void soundBounce();
};