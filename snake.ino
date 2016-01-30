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

int i_delay = 1000;
int a_direction[2];
int a_snake[70][2];
int a_apple[2];
int i_length = 1;

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
  }
  else if (a_direction[0] == -1) {
    a_direction[0] = 0;
    a_direction[1] = -1;
  }
  else if (a_direction[1] == 1) {
    a_direction[0] = 1;
    a_direction[1] = 0;
  }
  else if (a_direction[1] == -1) {
    a_direction[0] = -1;
    a_direction[1] = 0;
  }
}

void turn_r() {
  
}

void next() {
  // letztes teil ablöschen
  sparkle.set(a_snake[i_length-1][0], a_snake[i_length-1][1], WHITE);

  // die schlange verschieben
  for (int i = 1; i < i_length; i++) {
    a_snake[i][0] = a_snake[i-1][0];
    a_snake[i][1] = a_snake[i-1][1];
  }
  
  // kopf neu setzen
  a_snake[0][0] += a_direction[0];
  a_snake[0][1] += a_direction[1];

  // auf apfel prüfen
  if (a_snake[0][0] == a_apple[0] && a_snake[0][1] == a_apple[1]) {
    i_length++;
    spawn_apple();
  }
  
  sparkle.set(a_snake[0][0], a_snake[0][1], SNAKE);
}

void loop() {
  delay(i_delay); 
  
  parse_cmd();

  next();

  sparkle.show();
}

void spawn_snake() {
  int x = random(10);
  int y = random(7);
  sparkle.set(x, y, SNAKE);
  a_snake[0][0] = x;
  a_snake[0][1] = y;
  
  /*a_apple[0] = x+3;
  a_apple[1] = y;
  sparkle.set(x+3,y, APPLE);*/
}

void spawn_apple() {
  int x,y;
  //do {
    x = random(10);
    y = random(7);
  //} while(field[x][y] == SNAKE);
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
