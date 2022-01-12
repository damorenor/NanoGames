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
#include "Circle.h"
#include "NanoBird.h"

Button selectBtn(4);
Button incBtn(6);
Button enterBtn(5);
Button backBtn(3);

Menu menu(display,selectBtn,incBtn,enterBtn,backBtn);
Circle circle(display);
NanoBird bird(display);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3D)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  selectBtn.config();
  incBtn.config();
  enterBtn.config();
  backBtn.config();

  bird.setup();

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
  if(menu.page==0) menu.show();
  if(menu.page==1) circle.show();
  if(menu.page==2) bird.show();
  display.display();
}
