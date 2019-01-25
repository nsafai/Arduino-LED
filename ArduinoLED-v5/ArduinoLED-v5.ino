#include <Adafruit_NeoPixel.h>

#include <gfxfont.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>

#include <Adafruit_NeoMatrix.h>

#include <gamma.h>

//#include <FastLED.h>
#define NUM_LEDS 256
#define DATA_PIN 6


 Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(32, 8, DATA_PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
  NEO_GRB            + NEO_KHZ800);
  
const uint16_t colors[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255) };

void setup() {
  matrix.begin();
  matrix.setTextWrap(false);
//  matrix.setBrightness(40);
  matrix.setTextColor(colors[0]);
//  matrix.setTextSize(0.5);
}

int x    = matrix.width();
int pass = 0;

void printRainbowText(String text) {
  matrix.fillScreen(0);
  matrix.setCursor(x,0);

  int lenOfWord = 6 * text.length();

  matrix.setTextColor(colors[0]);
  matrix.print(text);
  
  if(--x < -lenOfWord) { // length of word in pixels
    x = matrix.width();
    if(++pass >= 3) pass = 0;
    matrix.setTextColor(colors[pass]);
  }
  matrix.show();
}


void loop() {
  printRainbowText("Hell yeah !");

  delay(50);
}

// where did we end: need to put loop inside of printRainbowText function
// use touch capacitor to change delay or word
// use switch to turn off


