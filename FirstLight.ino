/*
  FirstLight.ino - Library for controlling the Sparkle Shield LED display.
  Created by Scotty Allen, December 24, 2015.
  Released under a GPL v2 license.
*/

#include <FastLED.h>
#include <SparkleShield.h>

#define BRIGHTNESS 8

SparkleShield sparkle;

void loop() {
  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 10; j++) {
      sparkle.set(j, i, CHSV(0, 128, 255));
      sparkle.show();
    }
    delay(500);
    for (int j = 0; j < 10; j++) {
      sparkle.set(j, i, CHSV(0, 0, 0));
    }
  }

  for (int i = 0; i <10; i++) {
    for (int j = 0; j < 7; j++) {
      sparkle.set(i, j, CHSV(0, 128, 255));
      sparkle.show();      
    }
    delay(500);
    for (int j = 0; j < 10; j++) {
      sparkle.set(i, j, CHSV(0,0,0));
    }
  }
  
}

void setup() {
  sparkle.setBrightness(BRIGHTNESS);
}
