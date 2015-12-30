#include <FastLED.h>
#include <SparkleShield.h>
#include <avr/wdt.h>

#define M_GAMEOVER "GAME OVER"
#define TEXT_COLOR CHSV(70, 255, 255)
#define BACKGROUND_COLOR CHSV(128, 255, 200)

#define BRIGHTNESS 16

#define RED CRGB(255, 0, 0)           //Podest
#define GREEN CRGB(0, 255, 0)     // L
#define BLUE CRGB(0, 0, 255)      // 4er Balken
#define YELLOW CRGB(255, 255, 0)  // Quadrat
#define GREY CRGB(255, 255, 255)  // J
#define LBLUE CRGB(255, 128, 0)  // S
#define PINK CRGB(255, 0, 255)  // Z
#define WHITE CRGB(0, 0, 0)

int block[4][2];
CRGB MOVING;

CRGB field[10][7];

bool b_gameover = false;
bool b_mover = false;
bool b_movel = false;

SparkleShield sparkle;


void spawn_element(int x, int e) {
  CRGB element;
  
  int r = e != -1 ? e : random(7);
  switch (r) {
    case 0:
      element = PINK;
      break;
    case 1:
      element = LBLUE;
      break;
    case 2:
      element = RED;
      break;
    case 3:
      element = YELLOW;
      break;
    case 4:
      element = GREY;
      break;
    case 5:
      element = GREEN;
      break;
    case 6:
      element = BLUE;
      break;
    default:
      break;
  }
  
  MOVING = element;
  
  if (element == PINK) {
    int randx = x != -1 ? x : random(5);
    block[0][0] = 0;
    block[0][1] = randx;
    block[1][0] = 0;
    block[1][1] = randx+1;
    block[2][0] = 1;
    block[2][1] = randx+1;
    block[3][0] = 1;
    block[3][1] = randx+2;

    for (int i = 0; i < 4; i++) {
      if (field[block[i][0]][block[i][1]] != WHITE) {
        b_gameover = true;
      }      
      sparkle.set(block[i][0], block[i][1], element);
    }
  }  
  if (element == LBLUE) {
    int randx = x != -1 ? x : random(5);
    block[0][0] = 1;
    block[0][1] = randx+1;
    block[1][0] = 0;
    block[1][1] = randx+1;
    block[2][0] = 0;
    block[2][1] = randx+2;
    block[3][0] = 1;
    block[3][1] = randx;

    for (int i = 0; i < 4; i++) {
      if (field[block[i][0]][block[i][1]] != WHITE) {
        b_gameover = true;
      }      
      sparkle.set(block[i][0], block[i][1], element);
    }
  }  
  if (element == GREY) {
    int randx = x != -1 ? x : random(6);
    block[0][0] = 0;
    block[0][1] = randx+1;
    block[1][0] = 1;
    block[1][1] = randx+1;
    block[2][0] = 2;
    block[2][1] = randx+1;
    block[3][0] = 2;
    block[3][1] = randx;

    for (int i = 0; i < 4; i++) {
      if (field[block[i][0]][block[i][1]] != WHITE) {
        b_gameover = true;
      }    
      sparkle.set(block[i][0], block[i][1], element);
    }
  }
  if (element == YELLOW) {
    int randx = x != -1 ? x : random(6);
    block[0][0] = 0;
    block[0][1] = randx;
    block[1][0] = 1;
    block[1][1] = randx;
    block[2][0] = 0;
    block[2][1] = randx+1;
    block[3][0] = 1;
    block[3][1] = randx+1;

    for (int i = 0; i < 4; i++) {
      if (field[block[i][0]][block[i][1]] != WHITE) {
        b_gameover = true;
      }    
      sparkle.set(block[i][0], block[i][1], element);
    } 
  }
  else if (element == RED) {
    int randx = x != -1 ? x : random(5);
    block[0][0] = 0;
    block[0][1] = randx+1;
    block[1][0] = 1;
    block[1][1] = randx;
    block[2][0] = 1;
    block[2][1] = randx+1;
    block[3][0] = 1;
    block[3][1] = randx+2;

    for (int i = 0; i < 4; i++) {
      if (field[block[i][0]][block[i][1]] != WHITE) {
        b_gameover = true;
      }    
      sparkle.set(block[i][0], block[i][1], element);
    } 
  }
  else if (element == BLUE) { 
    int randx = x != -1 ? x : random(7);
    block[0][0] = 0;
    block[0][1] = randx;
    block[1][0] = 1;
    block[1][1] = randx;
    block[2][0] = 2;
    block[2][1] = randx;
    block[3][0] = 3;
    block[3][1] = randx;

    for (int i = 0; i < 4; i++) {
      if (field[block[i][0]][block[i][1]] != WHITE) {
        b_gameover = true;
      }    
      sparkle.set(block[i][0], block[i][1], element);
    } 
  }
  else if (element == GREEN) { 
    int randx = x != -1 ? x : random(6);
    block[0][0] = 0;
    block[0][1] = randx;
    block[1][0] = 1;
    block[1][1] = randx;
    block[2][0] = 2;
    block[2][1] = randx;
    block[3][0] = 2;
    block[3][1] = randx+1;

    for (int i = 0; i < 4; i++) {
      if (field[block[i][0]][block[i][1]] != WHITE) {
        b_gameover = true;
      }    
      sparkle.set(block[i][0], block[i][1], element);
    } 
  }
}


int calc_bottom(int y) {
  for (int i = 9; i > 0; i--) {
    if (field[i][y] == WHITE) {
      return i;  
    }
  }
  
  return 0;
}


void update_field() {  
  bool b_move = true;

  for (int i = 0; i < 4; i++) {
    // Collision detectionu
    if (field[block[i][0]+1][block[i][1]] != WHITE) {
      b_move = false;
    }
  }

  if (b_move)
  {
    for (int i = 0; i < 4; i++) {
      sparkle.set(block[i][0]+1, block[i][1], MOVING);
      block[i][0]++;
      bool b_top = true;
      for (int j = 0; j < 4; j++){
        if (block[j][0] ==  block[i][0]-1 && block[j][1] == block[i][1]) {
          b_top = false;
        }
      }
      if(b_top) {
        sparkle.set(block[i][0]-1, block[i][1], WHITE);
      }
    }
    
    //parse_cmd();
  }
  else {
    for (int i = 0; i < 4; i++) {
      field[block[i][0]][block[i][1]] = MOVING;
    }
    spawn_element(-1, -1);
  }
  
  // Full Row detection
  for (int i = 0; i < 6; i++) {
    bool full = true;
    for (int j = 0; j < 9; j++) {
      if (field[i][j] == WHITE) {
        full = false;
      }
    }
    if (full) {
      gameover();
    }
  }
}

void gameover() {
    /*sparkle.clear(BACKGROUND_COLOR);
    sparkle.scroll_text(M_GAMEOVER, TEXT_COLOR);
    sparkle.show(); */
    delay(100);
    sparkle.clear(CHSV(0, 0, 0));
    delay(100);
    setup();
    b_gameover = false;
}

void parse_cmd(){
  while (Serial.available()) {
    switch (Serial.read()) {
      uint16_t x, e;
      case 's':
        x = Serial.parseInt();
        e = Serial.parseInt();
        spawn_element(x, e);
        break;
      case 'r':
        b_mover = true;
        break;
      case 'l':
        b_movel = true;
        break;
      default:
        break;
    }
  }
}

void mover() {
  bool b_canmove = true;
  for (int i = 0; i < 4; i++) {
    // Collision detection
    if (field[block[i][0]][block[i][1]+1] != WHITE || block[i][1] > 5) {
      b_canmove = false;
    }
  }
  
  if (b_canmove) {
    for (int i = 0; i < 4; i++) {
      sparkle.set(block[i][0], block[i][1]+1, MOVING);
      block[i][1]++;
      bool b_top = true;
      for (int j = 0; j < 4; j++){
        if (block[j][1] ==  block[i][1]-1 && block[j][0] == block[i][0]) {
          b_top = false;
        }
      }
      if(b_top) {
        sparkle.set(block[i][0], block[i][1]-1, WHITE);
      }
    }
  }
  b_mover = false;
}

void movel() {
  bool b_canmove = true;
  for (int i = 0; i < 4; i++) {
    // Collision detection
    if (field[block[i][0]][block[i][1]-1] != WHITE || block[i][1] < 1) {
      b_canmove = false;
    }
  }
  
  if (b_canmove) {
    for (int i = 0; i < 4; i++) {
      sparkle.set(block[i][0], block[i][1]-1, MOVING);
      block[i][1]--;
      bool b_top = true;
      for (int j = 0; j < 4; j++){
        if (block[j][1] ==  block[i][1]+1 && block[j][0] == block[i][0]) {
          b_top = false;
        }
      }
      if(b_top) {
        sparkle.set(block[i][0], block[i][1]+1, WHITE);
      }
    }
  }
  b_movel = false;
}

void loop() {
  delay(500); 
  
  parse_cmd();

  if (b_gameover) {
    gameover();
  }
  else {
    update_field(); 
  }
  if (b_mover) {
    mover();
  }
  else if(b_movel) {
    movel();
  }

  sparkle.show();
}

void setup() {
  sparkle.setBrightness(BRIGHTNESS);
  
  wdt_disable();
  Serial.begin(115200);
  Serial.println("starting round");

  for(int i = 0; i < 10; i++) {
    for(int j = 0; j < 7; j++) {
      field[i][j] = WHITE;
      sparkle.set(i, j, WHITE);
    }
  }
  
  //spawn_element(-1, -1);
  sparkle.show();
}