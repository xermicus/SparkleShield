#include <FastLED.h>
#include <SparkleShield.h>

#define BRIGHTNESS 16

#define RED CRGB(255, 0, 0)           //Podest
#define GREEN CRGB(0, 255, 0)     // L
#define BLUE CRGB(0, 0, 255)      // 4er Balken
#define YELLOW CRGB(255, 255, 0)  // Quadrat
#define GREY CRGB(128, 128, 128)  // J
//#define WHITE CHSV(0, 0, 64)
#define WHITE CRGB(0, 0, 0)

int block[4][2];
CRGB MOVING;

CRGB field[10][7];
//CRGB cp_field[10][7];


SparkleShield sparkle;

void spawn_element(CRGB element) {
  int randx = 4;
  MOVING = element;  
  if (element == GREY) {
    block[0][0] = 0;
    block[0][1] = randx+1;
    block[1][0] = 1;
    block[1][1] = randx+1;
    block[2][0] = 2;
    block[2][1] = randx+1;
    block[3][0] = 2;
    block[3][1] = randx;

    for (int i = 0; i < 4; i++) {
      //field[block[i][0]][block[i][1]] = element;
      sparkle.set(block[i][0], block[i][1], element);
    }
  }
  if (element == YELLOW) {
    block[0][0] = 0;
    block[0][1] = randx;
    block[1][0] = 1;
    block[1][1] = randx;
    block[2][0] = 0;
    block[2][1] = randx+1;
    block[3][0] = 1;
    block[3][1] = randx+1;

    for (int i = 0; i < 4; i++) {
      //field[block[i][0]][block[i][1]] = element;
      sparkle.set(block[i][0], block[i][1], element);
    } 
  }
  else if (element == RED) { 
    int randx = 1;
    field[0][randx+1] = element;
    sparkle.set(0, randx+1, element); 
    field[1][randx] = element;
    sparkle.set(1, randx, element); 
    field[1][randx+1] = element;
    sparkle.set(1, randx+1, element); 
    field[1][randx+2] = element;
    sparkle.set(1, randx+2, element); 
  }
  else if (element == BLUE) { 
    int randx = 1;
    field[0][randx] = element;
    sparkle.set(0, randx, element); 
    field[1][randx] = element;
    sparkle.set(1, randx, element); 
    field[2][randx] = element;
    sparkle.set(2, randx, element); 
    field[3][randx] = element;
    sparkle.set(3, randx, element); 
  }
  else if (element == GREEN) { 
    int randx = 1;
    field[0][randx] = element;
    sparkle.set(0, randx, element); 
    field[1][randx] = element;
    sparkle.set(1, randx, element); 
    field[2][randx] = element;
    sparkle.set(2, randx, element); 
    field[2][randx+1] = element;
    sparkle.set(2, randx+1, element); 
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
  CRGB cp_field[10][7] = field;
  int i_bottom = 0;
  bool b_move = true;

  for (int i = 0; i < 4; i++) {
    if (cp_field[block[i][0]+1][block[i][1]] != WHITE) {
      b_move = false;
    }
  }

  if (b_move)
  {
    for (int i = 0; i < 4; i++) {
      sparkle.set(block[i][0]+1, block[i][1], MOVING);
      block[i][0]++;
      bool b_top = true;
      //int i_top = block[i][0];
      for (int j = 0; j < 4; j++){
        if (block[j][0] ==  block[i][0]-1 && block[j][1] == block[i][1]) {
          //i_top = block[j][0];
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
    spawn_element(YELLOW);
  }
  
}

void loop() {
  delay(300);  
  update_field();

  sparkle.show();
}

void setup() {
  sparkle.setBrightness(BRIGHTNESS);

  for(int i = 0; i < 10; i++) {
    for(int j = 0; j < 7; j++) {
      field[i][j] = WHITE;
      sparkle.set(i, j, WHITE);
    }
  }
  
  spawn_element(GREY);
  sparkle.show();
}