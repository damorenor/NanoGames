#pragma once

#include <Arduino.h>

class Button {
  private:
  int pin;
  unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
  unsigned long debounceDelay = 20;    // the debounce time; increase if the output flickers
  bool buttonState=HIGH;               // the current reading from the input pin
  bool lastButtonState = HIGH;         // the previous reading from the input pin
  
  public:  
  Button(int pin);
  void config();
  bool closed();
  bool wasPressed();
}; 

