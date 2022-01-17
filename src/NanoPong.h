#pragma once

#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include "Beeper.h"

class NanoPong
{
  private:
    Adafruit_SSD1306& display;
    Beeper& beeper;
    int paddleLocationA = 0;
    int paddleLocationB = 0;
    float ballX = 127/2;
    float ballY = 63/2;
    float ballSpeedX = 2;
    float ballSpeedY = 1;
    int lastPaddleLocationA = 0;
    int lastPaddleLocationB = 0;
    int scoreA = 0;
    int scoreB = 0;
    void splash();
    void calculateMovement();
    void draw();
    void addEffect(int paddleSpeed);
    void centerPrint(char *text, int y, int size);
  public:
    NanoPong(Adafruit_SSD1306& display, Beeper& beeper);
    void setup();
    void show();
};