#pragma once

#include <Arduino.h>
#include <Adafruit_SSD1306.h>

class Credits
{
  private:
  Adafruit_SSD1306& oled;
  public:
  Credits(Adafruit_SSD1306& oled);
  void show();
};