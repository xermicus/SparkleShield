#include <FastLED.h>
#include <SparkleShield.h>

#define BRIGHTNESS 16

#define RED CRGB(255, 0, 0) 
#define RED_BOTTOM CRGB(255, 0, 255)     
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
  int i_bottom;
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 7; j++) {
      i_bottom = calc_bottom(j);
      if (cp_field[i][j] != WHITE && i < i_bottom) {
        field[i+1][j] = cp_field[i][j];
        sparkle.set(i+1, j, cp_field[i][j]);
        if(cp_field[i-1][j] == WHITE || i < 1) {
          field[i][j] = WHITE;
          sparkle.set(i, j, WHITE);
        }
        // Spawn new
        if(i+1 == i_bottom) {
          spawn_element(YELLOW);
        }
      }
    }
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
  
  spawn_element(RED);
  spawn_element(YELLOW);
  sparkle.show();
}