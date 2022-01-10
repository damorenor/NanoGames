#include "Menu.h"

Menu::Menu(Adafruit_SSD1306& oled,Button& selectBtn,Button& incBtn,Button& enterBtn,Button& backBtn)
:oled(oled),selectBtn(selectBtn),incBtn(incBtn),enterBtn(enterBtn),backBtn(backBtn){}

void Menu::show()             
{
  oled.setTextColor(WHITE);
  oled.setCursor(35,0);
  oled.print("MENU");
  //indicator
  oled.setCursor(10,selIndPosY[option]);
  oled.print("->");  
  //labels
  oled.setCursor(35,10);
  oled.print("CIRCLE");
  //press info
  oled.setCursor(5,50);
  oled.print("press enter btn..."); 
}

void Menu::moveInd()  //move the selection Indicator
{
  if(selectBtn.wasPressed())
  {
    if(option<2) option++;
    else option=0;    
  }
}

void Menu::run()  //acivate redLed blinking
{

  if(option==0)
  {
    if(enterBtn.wasPressed())
    {
      page=1;
    }
  }
  else if(option==1)
  {
    if(enterBtn.wasPressed())
    {
      page=2;
    }    
  }
  else if(option==1)
  {
    if(enterBtn.wasPressed())
    {
      page=3;
    }    
  }

  if(backBtn.wasPressed())
  {
    page=0;
  }
}