#pragma once

#include <Arduino.h>
#include <Adafruit_SSD1306.h>

class Circle
{
  private:
  Adafruit_SSD1306& oled;
  public:
  Circle(Adafruit_SSD1306& oled);
  void show();
};