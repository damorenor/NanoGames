#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH        128 // OLED display width, in pixels
#define SCREEN_HEIGHT        64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET            4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#include <ArduinoTrace.h>
#include "Button.h"
#include "Menu.h"
#include "Credits.h"
#include "NanoBird.h"
#include "NanoPong.h"

Button selectBtn(4);
Button incBtn(6);
Button enterBtn(5);
Button backBtn(3);

bool state = false;
Menu menu(display,selectBtn,incBtn,enterBtn,backBtn);
Beeper beeper(3);
NanoBird bird(display);
NanoPong pong(display,beeper);
Credits credits(display);

void setButtons(){
  selectBtn.config();
  incBtn.config();
  enterBtn.config();
  backBtn.config();
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  setButtons();
}

void loop() {
  // put your main code here, to run repeatedly:
  menu.moveInd();
  menu.run();
  draw();
}

void draw()
{
  display.clearDisplay();
  if(menu.page==0){
    display.setTextSize(1);
    state=false;
    menu.show();
  }
  if(menu.page==1){
    if(!state){
      state=true;
      pong.setup();
      setButtons();
    }
    pong.show();
  }
  if(menu.page==2){
    if(!state){
      state=true;
      bird.setup();
      setButtons();
    }
    bird.show();
  }
  if(menu.page==3) credits.show();
  display.display();
}
