#include "NanoPong.h"

#define CONTROL_A A1
#define CONTROL_B A2

//Define Visuals
#define FONT_SIZE 2
#define SCREEN_WIDTH 127  //real size minus 1, because coordinate system starts with 0
#define SCREEN_HEIGHT 63  //real size minus 1, because coordinate system starts with 0
#define PADDLE_WIDTH 4
#define PADDLE_HEIGHT 10
#define PADDLE_PADDING 10
#define BALL_SIZE 3
#define SCORE_PADDING 10
  
#define EFFECT_SPEED 0.5
#define MIN_Y_SPEED 0.5
#define MAX_Y_SPEED 2

NanoPong::NanoPong(Adafruit_SSD1306& display, Beeper& beeper):display(display),beeper(beeper){}

void NanoPong::setup() 
{
  // clears the screen and buffer
  display.display();   
  display.setTextWrap(false);

  splash();
  
  display.setTextColor(WHITE);
  display.setTextSize(FONT_SIZE);
  display.clearDisplay(); 
}

void NanoPong::splash()
{
  display.setTextColor(WHITE);
  centerPrint("PONG",0,3);
  centerPrint("By Allan Alcorn",24,1);
  centerPrint("Ported by",33,1);
  centerPrint("MichaelTeeuw.nl",42,1);

  display.fillRect(0,SCREEN_HEIGHT-10,SCREEN_WIDTH,10,WHITE);
  display.setTextColor(BLACK);
  centerPrint("Move paddle to start!",SCREEN_HEIGHT-9,1);

  display.display();

  int controlA = analogRead(CONTROL_A);
  int controlB = analogRead(CONTROL_B);

  while (abs(controlA - analogRead(CONTROL_A) + controlB - analogRead(CONTROL_B)) < 10) {
    // show as long as the total absolute change of 
    // both potmeters is smaler than 5
  }

  beeper.soundStart();
}

//Loop
void NanoPong::show()
{
  calculateMovement();
  draw();
}

void NanoPong::calculateMovement() 
{
  int controlA = analogRead(CONTROL_A);
  int controlB = analogRead(CONTROL_B);

  paddleLocationA = map(controlA, 0, 1023, 0, SCREEN_HEIGHT - PADDLE_HEIGHT);
  paddleLocationB = map(controlB, 0, 1023, 0, SCREEN_HEIGHT - PADDLE_HEIGHT);

  int paddleSpeedA = paddleLocationA - lastPaddleLocationA;
  int paddleSpeedB = paddleLocationB - lastPaddleLocationB;

  ballX += ballSpeedX;
  ballY += ballSpeedY;

  //bounce from top and bottom
  if (ballY >= SCREEN_HEIGHT - BALL_SIZE || ballY <= 0) {
    ballSpeedY *= -1;
    beeper.soundBounce();
  }

  //bounce from paddle A
  if (ballX >= PADDLE_PADDING && ballX <= PADDLE_PADDING+BALL_SIZE && ballSpeedX < 0) {
    if (ballY > paddleLocationA - BALL_SIZE && ballY < paddleLocationA + PADDLE_HEIGHT) {
      beeper.soundBounce();
      ballSpeedX *= -1;
    
      addEffect(paddleSpeedA);
    }

  }

  //bounce from paddle B
  if (ballX >= SCREEN_WIDTH-PADDLE_WIDTH-PADDLE_PADDING-BALL_SIZE && ballX <= SCREEN_WIDTH-PADDLE_PADDING-BALL_SIZE && ballSpeedX > 0) {
    if (ballY > paddleLocationB - BALL_SIZE && ballY < paddleLocationB + PADDLE_HEIGHT) {
      beeper.soundBounce();
      ballSpeedX *= -1;
    
      addEffect(paddleSpeedB);
    }

  }

  //score points if ball hits wall behind paddle
  if (ballX >= SCREEN_WIDTH - BALL_SIZE || ballX <= 0) {
    if (ballSpeedX > 0) {
      scoreA++;
      ballX = SCREEN_WIDTH / 4;
    }
    if (ballSpeedX < 0) {
      scoreB++;
      ballX = SCREEN_WIDTH / 4 * 3;
    }

    beeper.soundPoint();   
  }

  //set last paddle locations
  lastPaddleLocationA = paddleLocationA;
  lastPaddleLocationB = paddleLocationB;  
}

void NanoPong::draw() 
{
  //draw paddle A
  display.fillRect(PADDLE_PADDING,paddleLocationA,PADDLE_WIDTH,PADDLE_HEIGHT,WHITE);

  //draw paddle B
  display.fillRect(SCREEN_WIDTH-PADDLE_WIDTH-PADDLE_PADDING,paddleLocationB,PADDLE_WIDTH,PADDLE_HEIGHT,WHITE);

  //draw center line
  for (int i=0; i<SCREEN_HEIGHT; i+=4) {
    display.drawFastVLine(SCREEN_WIDTH/2, i, 2, WHITE);
  }

  //draw ball
  display.fillRect(ballX,ballY,BALL_SIZE,BALL_SIZE,WHITE);

  //print scores

  //backwards indent score A. This is dirty, but it works ... ;)
  int scoreAWidth = 5 * FONT_SIZE;
  if (scoreA > 9) scoreAWidth += 6 * FONT_SIZE;
  if (scoreA > 99) scoreAWidth += 6 * FONT_SIZE;
  if (scoreA > 999) scoreAWidth += 6 * FONT_SIZE;
  if (scoreA > 9999) scoreAWidth += 6 * FONT_SIZE;

  display.setCursor(SCREEN_WIDTH - SCORE_PADDING - scoreAWidth,0);
  display.print(scoreA);

  display.setCursor(SCREEN_WIDTH/2 + SCORE_PADDING+1,0); //+1 because of dotted line.
  display.print(scoreB);
  
  display.display();
} 

void NanoPong::addEffect(int paddleSpeed)
{
  float oldBallSpeedY = ballSpeedY;

  //add effect to ball when paddle is moving while bouncing.
  //for every pixel of paddle movement, add or substact EFFECT_SPEED to ballspeed.
  for (int effect = 0; effect < abs(paddleSpeed); effect++) {
    if (paddleSpeed > 0) {
      ballSpeedY += EFFECT_SPEED;
    } else {
      ballSpeedY -= EFFECT_SPEED;
    }
  }

  //limit to minimum speed
  if (ballSpeedY < MIN_Y_SPEED && ballSpeedY > -MIN_Y_SPEED) {
    if (ballSpeedY > 0) ballSpeedY = MIN_Y_SPEED;
    if (ballSpeedY < 0) ballSpeedY = -MIN_Y_SPEED;
    if (ballSpeedY == 0) ballSpeedY = oldBallSpeedY;
  }

  //limit to maximum speed
  if (ballSpeedY > MAX_Y_SPEED) ballSpeedY = MAX_Y_SPEED;
  if (ballSpeedY < -MAX_Y_SPEED) ballSpeedY = -MAX_Y_SPEED;
}

void NanoPong::centerPrint(char *text, int y, int size)
{
  display.setTextSize(size);
  display.setCursor(SCREEN_WIDTH/2 - ((strlen(text))*6*size)/2,y);
  display.print(text);
}
