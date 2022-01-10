  #include "Button.h"

  Button::Button(int pin) {
    this->pin = pin;
  }

  void Button::config()
  {
    pinMode(pin,INPUT_PULLUP);
  }
  
  bool Button::closed() {
    if (digitalRead(pin)==LOW) return true;
    else return false; 
  }

  bool Button::wasPressed()
  {
  bool ready=false;
  // read the state of the switch into a local variable: 
  int reading = digitalRead(pin);
  
   // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only increment the counter if the new button state is LOW
      if (buttonState == LOW) {
        ready=true;
        //Serial.println(counter);       
      }
    }
  }
  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
  return ready;

  }