/*
  FirstLight.ino - Library for controlling the Sparkle Shield LED display.
  Created by Scotty Allen, December 24, 2015.
  Released under a GPL v2 license.
*/

// Light up each LED, one after another, starting at LED1, ending at LED70.

#include <FastLED.h>
#include <SparkleShield.h>

#define BRIGHTNESS 8

SparkleShield sparkle;

void loop() {
  // Step through the rows
  /*for(int y = 0; y < 7; y++) {
    // Step through the columns
    for(int x = 0; x < 10; x++) {
      // Set the current LED to be white:
      //  - hue: doesn't matter
      //  - saturation: zero, so there's no color
      //  - value: full brightness
      sparkle.set(x, y, CHSV(0, 128, 255));

      // Send the colors to the LEDs.
      sparkle.show();

      // Wait 0.1 seconds, so we have time to see the LED light up.
      delay(50);

      // Turn the LED off again, so it doesn't stay lit when we move onto the next led.
      sparkle.set(x, y, CHSV(0, 0, 0));
    }
  }*/
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
