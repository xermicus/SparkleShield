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

CRGB field[10][7];

bool b_gameover = false;
bool b_mover = false;
bool b_movel = false;
bool b_enter = false;

int i_delay = 500;
int i_direction[1][1];

SparkleShield sparkle;


void parse_cmd(){
  while (Serial.available()) {
    switch (Serial.read()) {
      uint16_t x;
      case 'd':
        b_mover = true;
        break;
      case 'a':
        b_movel = true;
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

void move() {
  
}

void loop() {
  delay(i_delay); 
  
  parse_cmd();

  sparkle.show();
}

void spawn_snake() {
  // clear
  for(int i = 0; i < 10; i++) {
    for(int j = 0; j < 7; j++) {
      field[i][j] = WHITE;
      sparkle.set(i, j, WHITE);
    }
  }
  int x = random(10);
  int y = random(7);
  field[x][y] = SNAKE;
  sparkle.set(x, y, SNAKE);
}

void spawn_apple() {
  int x,y;
  do {
    x = random(10);
    y = random(7);
  } while(field[x][y] == SNAKE);
  field[x][y] = APPLE;
  sparkle.set(x,y, APPLE);
}

void setup() {
  sparkle.setBrightness(BRIGHTNESS);

  randomSeed(analogRead(0));
  
  wdt_disable();
  Serial.begin(115200);
  Serial.println("starting round");

  spawn_snake();
  spawn_apple();
  
  sparkle.show();
}
