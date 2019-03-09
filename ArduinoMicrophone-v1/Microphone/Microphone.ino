#include <Adafruit_NeoMatrix.h>
#include <gamma.h>
//
//#include <FastLED.h>
//#define NUM_LEDS 256
//#define DATA_PIN 6

//uint16_t gHue = 0;
//uint8_t  gHueDelta = 3;
//int hue;
//CRGB leds[NUM_LEDS];
 
const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;
 
void setup() 
{
  delay(3000); 
  Serial.begin(9600);
//  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}
 
 
void loop() {
  printMicData();
}

void printMicData() {
  unsigned long startMillis= millis();  // Start of sample window
  unsigned int peakToPeak = 0;   // peak-to-peak level
  
  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;
  
  // collect data for 50 mS
  while (millis() - startMillis < sampleWindow)
  {
    sample = analogRead(0);
    if (sample < 1024)  // toss out spurious readings
    {
       if (sample > signalMax)
       {
          signalMax = sample;  // save just the max levels
       }
       else if (sample < signalMin)
       {
          signalMin = sample;  // save just the min levels
       }
    }
  }
  peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
  double volts = (peakToPeak * 5.0) / 1024;  // convert to volts
  
  Serial.println(volts);
  
//  prettyLights(volts);
}

//void prettyLights(double volts) {
//  int ledPerRow = 8;
//  int numRows = 32;
//  
//  Serial.println(volts);
//  if (volts > 0.2) {
//    for(int i = 0; i < 8; i++) {
//      for (int j = 0; j < numRows; j++) {
//        leds[i+j].setHue(1000*volts);
//      }
//      FastLED.show();
//      delay(30);
////      leds[i] = CRGB::Black;
//    }
//    FastLED.clear();
//  }
//}
//
//void rainbow() {
//  int numColors = 8;
//  int rgb = 255;
//  
//  for(int dot = 0; dot < NUM_LEDS; dot++) {
//    for (int color = 0; color < numColors; color++) {
//      leds[dot].setHue(dot);
//      leds[dot+1].setHue(dot+31);
//      leds[dot+2].setHue(dot+31*2);
//      leds[dot+3].setHue(dot+31*3);
//      leds[dot+4].setHue(dot+31*4);
//      leds[dot+5].setHue(dot+31*5);
//      leds[dot+6].setHue(dot+31*6);
//      leds[dot+7].setHue(dot+31*7);
//      FastLED.show();
//      // clear this led for the next time around the loop
//      leds[dot] = CRGB::Black;
//      leds[dot+1] = CRGB::Black;
//      leds[dot+2] = CRGB::Black;
//      leds[dot+3] = CRGB::Black;
//      leds[dot+4] = CRGB::Black;
//      leds[dot+5] = CRGB::Black;
//      leds[dot+6] = CRGB::Black;
//      leds[dot+7] = CRGB::Black;
////      delay(100); 
//    }
//  }
//}

