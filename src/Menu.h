#pragma once

#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <ArduinoTrace.h>
#include "Button.h"

class Menu
{
  private:
  Adafruit_SSD1306& oled;
  Button& selectBtn;
  Button& incBtn;
  Button& enterBtn;
  Button& backBtn;
  int option=0;
  int selIndPosY[4]={10,20,30,40};
  public:
  int page=0;
  Menu(Adafruit_SSD1306& oled,Button& selectBtn,Button& incBtn,Button& enterBtn,Button& backBtn);
  void show();
  void moveInd();
  void run();
};