
#include <FastLED.h>
#define NUM_LEDS 256
#define LED_PIN 6
#define COLOR_ORDER GRB
#define BRIGHTNESS  64

uint16_t gHue = 0;
uint8_t  gHueDelta = 3;

int hue;
 
CRGB leds[NUM_LEDS];

 
void setup() {
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
}
 
void loop() {

  for(int dot = 0; dot < NUM_LEDS; dot++) {
      
      leds[dot].setHue(dot);
      FastLED.show();
      // clear this led for the next time around the loop  
      delay(10);
      leds[dot] = CRGB::Black;
  }
}
