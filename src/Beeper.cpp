#include "Beeper.h"

Beeper::Beeper(int pinBeeper)
{
 this->pinBeeper = pinBeeper;
}

void Beeper::setup()
{
  pinMode(pinBeeper, OUTPUT);
}

void Beeper::soundStart()
{
  tone(pinBeeper, 250);
  delay(100);
  tone(pinBeeper, 500);
  delay(100);
  tone(pinBeeper, 1000);
  delay(100);
  noTone(pinBeeper);
}

void Beeper::soundPoint()
{
  tone(pinBeeper, 150, 50);
}

void Beeper::soundBounce()
{
  tone(pinBeeper, 500, 50);
}