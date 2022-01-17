#include "NanoBird.h"

NanoBird::NanoBird(Adafruit_SSD1306& display):display(display){}

  // pin the flap button is attached to
#define FLAP_BUTTON  5

// Initialise 'sprites'
#define SPRITE_HEIGHT   16
#define SPRITE_WIDTH    16

// Two frames of animation
static const unsigned char PROGMEM wing_down_bmp[] =
{ B00000000, B00000000,
  B00000000, B00000000,
  B00000011, B11000000,
  B00011111, B11110000,
  B00111111, B00111000,
  B01111111, B11111110,
  B11111111, B11000001,
  B11011111, B01111110,
  B11011111, B01111000,
  B11011111, B01111000,
  B11001110, B01111000,
  B11110001, B11110000,
  B01111111, B11100000,
  B00111111, B11000000,
  B00000111, B00000000,
  B00000000, B00000000,
};

static const unsigned char PROGMEM wing_up_bmp[] =
{ B00000000, B00000000,
  B00000000, B00000000,
  B00000011, B11000000,
  B00011111, B11110000,
  B00111111, B00111000,
  B01110001, B11111110,
  B11101110, B11000001,
  B11011111, B01111110,
  B11011111, B01111000,
  B11111111, B11111000,
  B11111111, B11111000,
  B11111111, B11110000,
  B01111111, B11100000,
  B00111111, B11000000,
  B00000111, B00000000,
  B00000000, B00000000,
};

// Game variables
#define GAME_SPEED 50

void NanoBird::setup()
{
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.clearDisplay();
  randomSeed(analogRead(0));
}

void NanoBird::show()
{
  if (game_state == 0) {
    // in game
    display.clearDisplay();

    // If the flap button is currently pressed, reduce the downward force on the bird a bit.
    // Once this foce goes negative the bird goes up, otherwise it falls towards the ground
    // gaining speed
    if (digitalRead(FLAP_BUTTON) == LOW) {
      momentum = -4;
    }

    // increase the downward force on the bird
    momentum += 1;

    // add the downward force to the bird position to determine it's new position
    bird_y += momentum;

    // make sure the bird doesn't fly off the top of the screen
    if (bird_y < 0 ) {
      bird_y = 0;
    }

    // make sure the bird doesn't fall off the bottom of the screen
    // give it a slight positive lift so it 'waddles' along the ground.
    if (bird_y > display.height() - SPRITE_HEIGHT) {
      bird_y = display.height() - SPRITE_HEIGHT;
      momentum = -2;
    }

    // display the bird
    // if the momentum on the bird is negative the bird is going up!
    if (momentum < 0) {

      // display the bird using a randomly picked flap animation frame
      if (random(2) == 0) {
        display.drawBitmap(bird_x, bird_y, wing_down_bmp, 16, 16, WHITE);
      }
      else {
        display.drawBitmap(bird_x, bird_y, wing_up_bmp, 16, 16, WHITE);
      }

    }
    else {

      // bird is currently falling, use wing up frame
      display.drawBitmap(bird_x, bird_y, wing_up_bmp, 16, 16, WHITE);

    }

    // now we draw the walls and see if the player has hit anything
    for (int i = 0 ; i < 2; i++) {

      // draw the top half of the wall
      display.fillRect(wall_x[i], 0, wall_width, wall_y[i], WHITE);

      // draw the bottom half of the wall
      display.fillRect(wall_x[i], wall_y[i] + wall_gap, wall_width, display.height() - wall_y[i] + wall_gap, WHITE);

      // if the wall has hit the edge of the screen
      // reset it back to the other side with a new gap position
      if (wall_x[i] < 0) {
        wall_y[i] = random(0, display.height() - wall_gap);
        wall_x[i] = display.width();
      }

      // if the bird has passed the wall, update the score
      if (wall_x[i] == bird_x) {
        score++;

        // highscore is whichever is bigger, the current high score or the current score
        high_score = max(score, high_score);
      }

      // if the bird is level with the wall and not level with the gap - game over!
      if (
        (bird_x + SPRITE_WIDTH > wall_x[i] && bird_x < wall_x[i] + wall_width) // level with wall
        &&
        (bird_y < wall_y[i] || bird_y + SPRITE_HEIGHT > wall_y[i] + wall_gap) // not level with the gap
      ) {
        
        // display the crash and pause 1/2 a second
        display.display();
        delay(500);

        // switch to game over state
        game_state = 1; 

      }

      // move the wall left 4 pixels
      wall_x[i] -= 4;
    }

    // display the current score
    boldTextAtCenter(0, (String)score);

    // now display everything to the user and wait a bit to keep things playable
    display.display();
    delay(GAME_SPEED);

  }
  else {

    // game over screen

    screenWipe(10);

    outlineTextAtCenter(1, "NANO BIRD");
    
    textAtCenter(display.height() / 2 - 8, "GAME OVER");
    textAtCenter(display.height() / 2, String(score));
    
    boldTextAtCenter(display.height() - 16, "HIGH SCORE");
    boldTextAtCenter(display.height()  - 8, String(high_score));

    display.display();

    // wait while the user stops pressing the button
    while (digitalRead(FLAP_BUTTON) == LOW);

    // setup a new game
    bird_y = display.height() / 2;
    momentum = -4;
    wall_x[0] = display.width() ;
    wall_y[0] = display.height() / 2 - wall_gap / 2;
    wall_x[1] = display.width() + display.width() / 2;
    wall_y[1] = display.height() / 2 - wall_gap / 1;
    score = 0;

    // wait until the user presses the button
    while (digitalRead(FLAP_BUTTON) == HIGH);

    // start a new game
    screenWipe(10);
    game_state = 0;
    
  }
}

void NanoBird::screenWipe(int speed)
{
  // progressivly fill screen with white
  for (int i = 0; i < display.height(); i += speed) {
    display.fillRect(0, i, display.width(), speed, WHITE);
    display.display();
  }

  // progressively fill the screen with black
  for (int i = 0; i < display.height(); i += speed) {
    display.fillRect(0, i, display.width(), speed, BLACK);
    display.display();
  }
}

void NanoBird::textAt(int x, int y, String txt)
{
  display.setCursor(x, y);
  display.print(txt);
}

void NanoBird::textAtCenter(int y, String txt)
{
  textAt(display.width() / 2 - txt.length() * 3, y, txt);
}

void NanoBird::outlineTextAtCenter(int y, String txt)
{
  int x = display.width() / 2 - txt.length() * 3;

  display.setTextColor(WHITE);
  textAt(x - 1, y, txt);
  textAt(x + 1, y, txt);
  textAt(x, y - 1, txt);
  textAt(x, y + 1, txt);

  display.setTextColor(BLACK);
  textAt(x, y, txt);
  display.setTextColor(WHITE);
}

void NanoBird::boldTextAtCenter(int y, String txt)
{
  int x = display.width() / 2 - txt.length() * 3;

  textAt(x, y, txt);
  textAt(x + 1, y, txt);
}