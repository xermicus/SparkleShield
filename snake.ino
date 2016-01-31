#include <FastLED.h>
#include <SparkleShield.h>
#include <avr/wdt.h>

#define M_GAMEOVER "GAME OVER"
#define TEXT_COLOR CHSV(70, 255, 255)
#define BACKGROUND_COLOR CHSV(128, 255, 200)

#define BRIGHTNESS 32

#define APPLE CRGB(255, 0, 0)
#define SNAKE CRGB(255, 255, 255)
#define WHITE CRGB(0, 0, 0)

bool b_gameover = false;
//bool b_mover = false;
//bool b_movel = false;
bool b_enter = false;

int i_delay = 750;
int a_direction[2];
int a_snake[70][2];
int a_apple[2];
int i_length = 1;

int a_head[2];
int a_last[2];

SparkleShield sparkle;


void parse_cmd(){
  while (Serial.available()) {
    switch (Serial.read()) {
      uint16_t x;
      case 'd':
        turn_r();
        break;
      case 'a':
        turn_l();
        break;
      case (char)13:
        b_enter = true;
        break;
      case 'q':
        //gameover();
        break;
      default:
        break;
    }
  }
}

void turn_l() {
  if (a_direction[0] == 1) {
    a_direction[0] = 0;
    a_direction[1] = 1;
    return;
  }
  else if (a_direction[0] == -1) {
    a_direction[0] = 0;
    a_direction[1] = -1;
    return;
  }
  else if (a_direction[1] == 1) {
    a_direction[0] = -1;
    a_direction[1] = 0;
    return;
  }
  else if (a_direction[1] == -1) {
    a_direction[0] = 1;
    a_direction[1] = 0;
    return;
  }
}

void turn_r() {
  if (a_direction[0] == 1) {
    a_direction[0] = 0;
    a_direction[1] = -1;
    return;
  }
  else if (a_direction[0] == -1) {
    a_direction[0] = 0;
    a_direction[1] = 1;
    return;
  }
  else if (a_direction[1] == 1) {
    a_direction[0] = 1;
    a_direction[1] = 0;
    return;
  }
  else if (a_direction[1] == -1) {
    a_direction[0] = -1;
    a_direction[1] = 0;
    return;
  }  
}

bool hit_snake(int x, int y) {
  for(int i = 0; i < i_length; i++) {
      if (x == a_snake[i][0] && y == a_snake[i][1]) {
        return true;
      }
  }
  
  return false;
}

void next() {
  for (int i = 0; i<i_length; i++) {
    sparkle.set(a_snake[i][0], a_snake[i][1], WHITE);
  }

  for(int i = i_length; i>0; i--) {
      a_snake[i][0] = a_snake[i-1][0];
      a_snake[i][1] = a_snake[i-1][1];
  }

  a_snake[0][0] = a_snake[1][0] + a_direction[0];
  a_snake[0][1] = a_snake[1][1] + a_direction[1];

  if (a_snake[0][0] == a_apple[0] && a_snake[0][1] == a_apple[1]) {
    spawn_apple();
    i_length++;
    if (i_delay > 100) {
      i_delay -=25;
    }
  }

  for (int i = 0; i<i_length; i++) {
    sparkle.set(a_snake[i][0], a_snake[i][1], SNAKE);
  }
}

void loop() {
  delay(i_delay); 
  
  parse_cmd();

  next();

  sparkle.show();
}

void spawn_snake() {
  i_length = 1;
  int x = random(10);
  int y = random(7);
  sparkle.set(x, y, SNAKE);
  a_snake[0][0] = x;
  a_snake[0][1] = y;
}

void spawn_apple() {
  int x,y;
  
  do {  
    x = random(10);
    y = random(7);
  } while(hit_snake(x, y));
  
  a_apple[0] = x;
  a_apple[1] = y;
  sparkle.set(x,y, APPLE);
}

void setup() {
  sparkle.setBrightness(BRIGHTNESS);

  randomSeed(analogRead(0));
  
  wdt_disable();
  Serial.begin(115200);
  Serial.println("starting round");

  a_direction[0] = 1;
  a_direction[1] = 0;

  spawn_snake();
  spawn_apple();
  
  sparkle.show();
}
