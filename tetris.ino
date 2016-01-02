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
#define LBLUE CRGB(0, 255, 128)  // S
#define PINK CRGB(255, 0, 255)  // Z
#define WHITE CRGB(0, 0, 0)

int block[4][2];
CRGB MOVING;

CRGB field[10][7];

bool b_gameover = false;
bool b_mover = false;
bool b_movel = false;
bool b_moved = false;

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
      else {      
        sparkle.set(block[i][0], block[i][1], element);
      }
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
      else {      
         sparkle.set(block[i][0], block[i][1], element);
      }
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
      else {  
        sparkle.set(block[i][0], block[i][1], element);
      }
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
      else {     
        sparkle.set(block[i][0], block[i][1], element);
      }
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
      else { 
        sparkle.set(block[i][0], block[i][1], element);
      }
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
      else { 
        sparkle.set(block[i][0], block[i][1], element);
      }
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
      else {   
        sparkle.set(block[i][0], block[i][1], element);
      }
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
    //check_fullrow();
    spawn_element(-1, -1);
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
      case 'e':
        x = Serial.parseInt();
        e = Serial.parseInt();
        spawn_element(x, e);
        break;
      case 'd':
        b_mover = true;
        break;
      case 'a':
        b_movel = true;
        break;
      case (char)13:
        b_moved = true;
        break;
      case 'q':
        gameover();
        break;
      case 's':
        rotate();
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

void moved() {
  bool b_move = true;

  while(b_move){
    for (int i = 0; i < 4; i++) {
      // Collision detectionu
      if (field[block[i][0]+1][block[i][1]] != WHITE) {
        b_move = false;
      }
    }
    if (b_move) {
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
    }
    else {
      for (int i = 0; i < 4; i++) {
          field[block[i][0]][block[i][1]] = MOVING;
      }

      spawn_element(-1, -1);
    }
  }
  
  b_moved = false;
}

void check_fullrow() {  
  bool b_switch = false;
  for (int i = 9; i > 0; i--) {
    bool full = true;
    for (int j = 0; j < 7; j++) {
      if (field[i][j] == WHITE) {
        full = false;
      }
    }
    if (full) {
      b_switch = true;
    }
    if (b_switch) {
      for (int j = 0; j < 7; j++) {
        field[i][j] = field[i-1][j];
        sparkle.set(i, j, field[i][j]);
        if (field[i-1][j] == WHITE) {
          field[i][j] = WHITE;
          sparkle.set(i, j, WHITE);
        }
        
      }
    }
  }
}

void rotate() {
  // Use Matrix
  //...
  
  if (MOVING == RED) {
    sparkle.set(block[2][0], block[2][1], WHITE);
    sparkle.set(block[3][0], block[3][1], WHITE);
    block[2][0] -= 1;
    block[2][1] -= 1;
    block[3][0] -= 2;
    block[3][1] -= 2;
    for(int i = 0; i < 4; i++) {
        sparkle.set(block[i][0], block[i][1], MOVING);
    }
  }
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
  else if(b_moved) {
    moved();
  }

  check_fullrow();

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