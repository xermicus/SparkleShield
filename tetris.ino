#include <FastLED.h>
#include <SparkleShield.h>

#define BRIGHTNESS 16

#define RED CRGB(255, 0, 0)     
#define GREEN CRGB(0, 255, 0)
#define BLUE CRGB(0, 0, 255)      // 4er Balken
#define YELLOW CRGB(255, 255, 0)  // Quadrat
#define YELLOW_BOTTOM CRGB(255, 255, 128)
//#define WHITE CHSV(0, 0, 64)
#define WHITE CRGB(0, 0, 0)

CRGB field[10][7];
int x_move;
int y_move;

SparkleShield sparkle;

void spawn_element(CRGB element) {
  int randx = 4;
  if (element == YELLOW) {    
    for (int i = 0; i < 2; i++){
      for (int j = randx; j < randx+2 ; j++) {       // insert random here (0..5, 2..7)
        field[i][j] = element;
        sparkle.set(i, j, field[i][j]);
      }      
    }
  }
}


int calc_bottom(int y) {
  for (int i = 9; i > 0; i--) {
    if (field[i][y] == WHITE) {
      return i-1;  
    }
  }
  
  return 0;
}


void update_field() {
  CRGB cp_field[10][7] = field;
  int i_bottom;
  for (int i = 1; i < 9; i++) {
    for (int j = 0; j < 7; j++) {
      i_bottom = calc_bottom(j);
      // YELLOW, move down
      if (cp_field[i][j] == YELLOW && cp_field[i+1][j] == WHITE) {
        field[i+1][j] = YELLOW;
        field[i-1][j] = WHITE;
        sparkle.set(i+1, j, YELLOW);
        sparkle.set(i-1, j, WHITE);
        // check for bottom
        if (i == i_bottom) {
          field[i][j] = YELLOW_BOTTOM;
          field[i+1][j] = YELLOW_BOTTOM;
          sparkle.set(i, j, field[i][j]);
          sparkle.set(i+1, j, field[i+1][j]);
          spawn_element(YELLOW);
        }
      }
    }
  }
}

void draw_field() {
  /*for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 7; j++) {
      /*if (field[i][j] != WHITE) {
        sparkle.set(i, j, field[i][j]);
      }
      else {
        sparkle.set(i, j, WHITE);
      }
    }
  }*/
}

void loop() {
  delay(200);  
  update_field();

  //draw_field();
  
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
  
  spawn_element(YELLOW);
  sparkle.show();
}