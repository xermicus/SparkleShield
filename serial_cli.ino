#include <FastLED.h>
#include <SparkleShield.h>
#include <avr/wdt.h>

#define BRIGHTNESS 16


SparkleShield sparkle;


void setup() {
  wdt_disable();
  Serial.begin(115200);
  Serial.println("hi there");
  
  sparkle.setBrightness(BRIGHTNESS);
}

void loop() {
  uint16_t x,y,r,g,b;
  while (Serial.available()) {
    switch (Serial.read()) {
/*      case 'r':
        wdt_enable(WDTO_1S);
        while(1) {} // block system and run into watchdog timeout
        break; */
      case 's': // 's 10 23 43'
       x = Serial.parseInt();
       y = Serial.parseInt();
       r = Serial.parseInt();
       g = Serial.parseInt();
       b = Serial.parseInt();
       sparkle.set(x, y, CRGB(r, g, b));
       break;
      case 'g':
       x = Serial.parseInt();
       y = Serial.parseInt();
      // Serial.print("D: getb ");
      // Serial.print(x); Serial.print(' ');
      // Serial.print(y); Serial.println(' ');
       Serial.print(   128 /* THE VALUE AT X Y */); Serial.println(' ');
      /*default:
        while( Serial.read()) {}   // flush corrupted buffer
        break;*/
   }   
    
  }

  delay(10);
  sparkle.show();
}