
#include <FastLED.h>
#define NUM_LEDS 256
#define LED_PIN 6
#define COLOR_ORDER GRB
#define BRIGHTNESS  64

uint16_t gHue = 0;
uint8_t  gHueDelta = 3;

int hue;
int dot = 0;
int columns = 32;
int rows = 8;

CRGB leds[NUM_LEDS];

 
void setup() {
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
  Serial.begin(9600);

}
 
void loop() {
    int led_array[] = {0, 1, 2, 3, 4, 5, 6, 7};
    for(int col = 0; col < columns; col++) {
        int *old_leds = led_array;
        Serial.print("Column: "); Serial.print(col); Serial.print("\n");
        Serial.print("LED: "); Serial.print(dot); Serial.print("\n");
        for(int led = 0; led < sizeof(led_array); led++){
          leds[led_array[led]].setHue(led_array[led]);
          if(col%2==0){
          // For every row down from the first, two LEDs less to travel to next led same row due to snake pattern
          led_array[led]+=15+led*(-2);
          }
         else{
          // For every row down from the first, two LEDs more to travel to next led same row due to snake pattern
          led_array[led]+=1+led*2;
          }
        FastLED.show();
        // clear this led for the next time around the loop  
        delay(10);
        }
        for(int led = 0; led < sizeof(led_array); led++){
          leds[old_leds[led]] = CRGB::Black;
        }
        
        
        
    }
}
