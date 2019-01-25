#include <Adafruit_NeoMatrix.h>
#include <gamma.h>

#include <FastLED.h>
#define NUM_LEDS 256
#define DATA_PIN 6

uint16_t gHue = 0;
uint8_t  gHueDelta = 3;

int hue;
 
CRGB leds[NUM_LEDS];
 
void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
//  leds[1].setHue(0);
//  leds[15].setHue(8);
//  FastLED.show();
}
 
void loop() {
//  for(int dot = 0; dot < NUM_LEDS; dot++) {
////    leds[dot].setHue(dot);
////    FastLED.show();
//  }
  for(int dot = 0; dot < NUM_LEDS; dot++) {
      
      leds[dot].setHue(dot);
      leds[dot+1].setHue(dot+31);
      leds[dot+2].setHue(dot+31*2);
      leds[dot+3].setHue(dot+31*3);
      leds[dot+4].setHue(dot+31*4);
      leds[dot+5].setHue(dot+31*5);
      leds[dot+6].setHue(dot+31*6);
      leds[dot+7].setHue(dot+31*7);
      FastLED.show();
      // clear this led for the next time around the loop
      leds[dot] = CRGB::Black;
      leds[dot+1] = CRGB::Black;
      leds[dot+2] = CRGB::Black;
      leds[dot+3] = CRGB::Black;
      leds[dot+4] = CRGB::Black;
      leds[dot+5] = CRGB::Black;
      leds[dot+6] = CRGB::Black;
      leds[dot+7] = CRGB::Black;
      delay(30);
  }
}
