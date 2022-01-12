#pragma once

#include <Arduino.h>
#include <Adafruit_SSD1306.h>

class NanoBird
{
  private:
    Adafruit_SSD1306& display;
    int game_state = 1; // 0 = game over screen, 1 = in game
    int score = 0; // current game score
    int high_score = 0; // highest score since the nano was reset
    int bird_x = (int)display.width() / 4; // birds x position (along) - initialised to 1/4 the way along the screen
    int bird_y; // birds y position (down)
    int momentum = 0; // how much force is pulling the bird down
    int wall_x[2]; // an array to hold the walls x positions
    int wall_y[2]; // an array to hold the walls y positions
    int wall_gap = 30; // size of the wall wall_gap in pixels
    int wall_width = 10; // width of the wall in pixels
    void screenWipe(int speed);
    void textAt(int x, int y, String txt);
    void textAtCenter(int y, String txt);
    void outlineTextAtCenter(int y, String txt);
    void boldTextAtCenter(int y, String txt);
  public:
    NanoBird(Adafruit_SSD1306& display);
    void setup();
    void show();
};