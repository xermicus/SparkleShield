#include <FastLED.h>
#include <SparkleShield.h>
#include <avr/wdt.h>

#define M_GAMEOVER "   GAME OVER"
#define TEXT_COLOR CHSV(70, 255, 255)
#define BACKGROUND_COLOR CHSV(128, 255, 200)

#define BRIGHTNESS 24

#define APPLE CRGB(255, 0, 0)
#define SNAKE CRGB(0, 255, 0)
#define WHITE CHSV(0, 0, 0)

//bool b_gameover = false;
bool b_pause = true;
bool b_mover = false;
bool b_movel = false;
bool b_bot = false;
bool b_infinitebot = false;

int i_delay = 550;
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
        b_mover = true;
        break;
      case 'a':
        b_movel = true;
        break;
      case (char)13:
        b_pause = b_pause ? false : true;
        break;
      case 'b':
        b_bot = b_bot ? false : true;
        if(b_bot) { Serial.println("bot on"); } else { Serial.println("bot off"); }
        break;
      case 'i':
        b_infinitebot = b_infinitebot ? false : true;
        if(b_infinitebot) { Serial.println("godmode on"); } else { Serial.println("godmode off"); }
        break;
      case 'q':
        gameover();
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

bool hit_snake(int x, int y, int offset) {
  for(int i = offset; i < i_length; i++) {
      if (x == a_snake[i][0] && y == a_snake[i][1]) {
        return true;
      }
  }  
  return false;
}

void bot() {
  int old_dir_y = a_direction[0];
  int old_dir_x = a_direction[1];
  
  if (!b_infinitebot)
  {
    if (a_snake[0][0] > a_apple[0]) {
      a_direction[0] = -1;
      a_direction[1] = 0;
    }
    else if (a_snake[0][0] < a_apple[0]) {
      a_direction[0] = 1;
      a_direction[1] = 0;
    }

    else if (a_snake[0][1] > a_apple[1]) {
      a_direction[0] = 0;
      a_direction[1] = -1;
    }
    else if (a_snake[0][1] < a_apple[1]) {
      a_direction[0] = 0;
      a_direction[1] = 1;
    }
  }
  if (b_infinitebot){
    if (a_snake[0][0] < 9 && a_snake[0][1] == 0) {
      a_direction[0] = 1;
      a_direction[1] = 0;
    }
    if (a_snake[0][0] == 9 && a_snake[0][1] == 0) {
      a_direction[0] = 0;
      a_direction[1] = 1;      
    }
    if (a_snake[0][0] == 9 && a_snake[0][1] == 6) {
      a_direction[0] = -1;
      a_direction[1] = 0;      
    }
    if (a_snake[0][0] == 8 && a_snake[0][1] == 6) {
      a_direction[0] = 0;
      a_direction[1] = -1;      
    }
    if (a_snake[0][0] == 8 && a_snake[0][1] == 1) {
      a_direction[0] = -1;
      a_direction[1] = 0;      
    }
    if (a_snake[0][0] == 7 && a_snake[0][1] == 1) {
      a_direction[0] = 0;
      a_direction[1] = 1;      
    }
    if (a_snake[0][0] == 7 && a_snake[0][1] == 6) {
      a_direction[0] = -1;
      a_direction[1] = 0;      
    }
    if (a_snake[0][0] == 6 && a_snake[0][1] == 6) {
      a_direction[0] = 0;
      a_direction[1] = -1;      
    }
    if (a_snake[0][0] == 6 && a_snake[0][1] == 1) {
      a_direction[0] = -1;
      a_direction[1] = 0;      
    }
    if (a_snake[0][0] == 5 && a_snake[0][1] == 1) {
      a_direction[0] = 0;
      a_direction[1] = 1;      
    }
    if (a_snake[0][0] == 5 && a_snake[0][1] == 6) {
      a_direction[0] = -1;
      a_direction[1] = 0;      
    }
    if (a_snake[0][0] == 4 && a_snake[0][1] == 6) {
      a_direction[0] = 0;
      a_direction[1] = -1;      
    }
    if (a_snake[0][0] == 4 && a_snake[0][1] == 1) {
      a_direction[0] = -1;
      a_direction[1] = 0;      
    }
    if (a_snake[0][0] == 3 && a_snake[0][1] == 1) {
      a_direction[0] = 0;
      a_direction[1] = 1;      
    }
    if (a_snake[0][0] == 3 && a_snake[0][1] == 6) {
      a_direction[0] = -1;
      a_direction[1] = 0;      
    }
    if (a_snake[0][0] == 2 && a_snake[0][1] == 6) {
      a_direction[0] = 0;
      a_direction[1] = -1;      
    }
    if (a_snake[0][0] == 2 && a_snake[0][1] == 1) {
      a_direction[0] = -1;
      a_direction[1] = 0;      
    }
    if (a_snake[0][0] == 1 && a_snake[0][1] == 1) {
      a_direction[0] = 0;
      a_direction[1] = 1;      
    }
    if (a_snake[0][0] == 1 && a_snake[0][1] == 6) {
      a_direction[0] = -1;
      a_direction[1] = 0;      
    }
    if (a_snake[0][0] == 0 && a_snake[0][1] == 6) {
      a_direction[0] = 0;
      a_direction[1] = -1;      
    }
  }
  
  if (hit_snake(a_snake[0][0] + a_direction[0], a_snake[0][1] + a_direction[1], 1)) {
    a_direction[0] = old_dir_y;
    a_direction[1] = old_dir_x;
  }
  if (hit_snake(a_snake[0][0] + a_direction[0], a_snake[0][1] + a_direction[1], 1)) {
    a_direction[0] = 0;
    a_direction[1] = 1;
  }
  if (hit_snake(a_snake[0][0] + a_direction[0], a_snake[0][1] + a_direction[1], 1)) {
    a_direction[0] = 1;
    a_direction[1] = 0;
  }
  if (hit_snake(a_snake[0][0] + a_direction[0], a_snake[0][1] + a_direction[1], 1)) {
    a_direction[0] = 0;
    a_direction[1] = -1;
  }
  if (hit_snake(a_snake[0][0] + a_direction[0], a_snake[0][1] + a_direction[1], 1)) {
    a_direction[0] = -1;
    a_direction[1] = 0;
  }
}

void next() {
  if (b_bot) {
    bot();
  }
  
  // turn
  if (b_mover) {
    turn_r();    
    b_mover = false;
  }
  if (b_movel) {
    turn_l();    
    b_movel = false;
  }

  for (int i = 0; i<i_length; i++) {
    sparkle.set(a_snake[i][0], a_snake[i][1], WHITE);
  }

  // move
  for(int i = i_length; i>0; i--) {
      a_snake[i][0] = a_snake[i-1][0];
      a_snake[i][1] = a_snake[i-1][1];
  }
  
  a_snake[0][0] = a_snake[1][0] + a_direction[0];
  a_snake[0][1] = a_snake[1][1] + a_direction[1];
  if(a_snake[0][0] > 9){
    a_snake[0][0] = 0;
  }
  if(a_snake[0][0] < 0){
    a_snake[0][0] = 9;
  }
  if(a_snake[0][1] > 6){
    a_snake[0][1] = 0;
  }
  if(a_snake[0][1] < 0){
    a_snake[0][1] = 6;
  }
  
  // gameover
  if (hit_snake(a_snake[0][0], a_snake[0][1], 1)) {
    gameover();
  }

  // apple
  if (a_snake[0][0] == a_apple[0] && a_snake[0][1] == a_apple[1]) {
    spawn_apple();
    i_length++;
    if (i_delay > 250) {
      i_delay -= 30;
    }
  }

  for (int i = 0; i<i_length; i++) {
    sparkle.set(a_snake[i][0], a_snake[i][1], SNAKE);
  }
}

void gameover() {
  // Score Animation
  char score[3];
  itoa(i_length, score, 10);  
  /*for (int i = 0; i < 1300; i++) {
    sparkle.clear(BACKGROUND_COLOR);
    sparkle.scroll_text(M_GAMEOVER, TEXT_COLOR);
    sparkle.show();
  }*/
  sparkle.clear();
  sparkle.draw_text(0,0,score,TEXT_COLOR);
  sparkle.show();
  delay(5000);

  // Reset
  a_direction[0] = 1;
  a_direction[1] = 0;

  spawn_snake();
  spawn_apple();

  i_delay = 550;

  b_pause = true;
}

void loop() {
  delay(i_delay); 
  
  parse_cmd();

  if (b_pause) {
    return;
  }

  next();

  sparkle.show();
}

void spawn_snake() {
  i_length = 1;
  int x = random(10);
  int y = random(7);
  a_snake[0][0] = x;
  a_snake[0][1] = y;
  sparkle.clear();
  sparkle.set(x, y, SNAKE);
}

void spawn_apple() {
  int x,y;
  
  do {  
    x = random(10);
    y = random(7);
  } while(hit_snake(x, y, 0));
  
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
  
  sparkle.clear(WHITE);

  a_direction[0] = 1;
  a_direction[1] = 0;

  spawn_snake();
  spawn_apple();
  
  sparkle.show();
}
