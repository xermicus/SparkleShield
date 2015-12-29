#include <FastLED.h>
#include <SparkleShield.h>

#define BRIGHTNESS 16

#define RED CRGB(255, 0, 0)     
#define GREEN CRGB(0, 255, 0)
#define BLUE CRGB(0, 0, 255)      // 4er Balken
#define YELLOW CRGB(255, 255, 0)  // Quadrat
#define YELLOW_BOTTOM CRGB(255, 255, 1);
//#define WHITE CHSV(0, 0, 64)
#define WHITE CRGB(30, 30, 30)

CRGB field[10][7];
int x_move;
int y_move;

SparkleShield sparkle;

void spawn_element(CRGB element) {
  if (element == YELLOW) {
    
    for (int i = 0; i < 2; i++){
      for (int j = 3; j < 5; j++) {       // insert random here (0..5, 2..7)
        field[i][j] = element;
        sparkle.set(i, j, field[i][j]);
      }      
    }
  }
}

void update_field() {
  CRGB cp_field[10][7] = field;
  
  for (int i = 1; i < 9; i++) {
    for (int j = 0; j < 7; j++) {
      // YELLOW
      if (cp_field[i][j] == YELLOW && cp_field[i+1][j] == WHITE) {
        
        field[i+1][j] = YELLOW;
        field[i-1][j] = WHITE;

      // BLUE

      // GREEN
      }
    }
  }
}

void draw_field() {
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 7; j++) {
      if (field[i][j] != WHITE) {
        sparkle.set(i, j, field[i][j]);
      }
      else {
        sparkle.set(i, j, WHITE);
      }
    }
  }
}

void loop() {
  update_field();

  draw_field();
  
  sparkle.show();
  delay(500);  
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