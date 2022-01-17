  #include "Credits.h"

  Credits::Credits(Adafruit_SSD1306& oled):oled(oled){}
  void  Credits::show()
  {
    oled.setCursor(35,10);
    oled.print("CREDITS");
    /*allocation fails :c
    oled.setCursor(5,20);
    oled.print("NanoGames by damorenor");
    oled.setCursor(5,30);
    oled.print("Pong by MichaelTeeuw");
    oled.setCursor(5,40);
    oled.print("NanoBird by richardathome");  */
    //labels
    oled.setCursor(5,50);
    oled.print("press back btn...");        
  }

 
