  #include "Circle.h"

  Circle::Circle(Adafruit_SSD1306& oled):oled(oled){}
  void  Circle::show()
  {
    oled.fillCircle(64,27,10,WHITE); 
    oled.setCursor(5,50);
    oled.print("press back btn...");        
  }

 
