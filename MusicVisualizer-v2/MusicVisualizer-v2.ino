#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <gamma.h>

#define NUM_LEDS 256
#define NUM_COL 32
#define NUM_ROWS 8
#define DATA_PIN 6
#define NUM_COLORS 8

const int sampleWindow = 8; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;

 Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(32, 8, DATA_PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
  NEO_GRB            + NEO_KHZ800);

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_LEDS, DATA_PIN, NEO_GRB + NEO_KHZ800);
  
const uint16_t rainbow_colors[] = {
  matrix.Color(255, 0, 0),
  matrix.Color(255, 63, 0),
  matrix.Color(255, 127, 0),
  matrix.Color(255, 255, 0),
  matrix.Color(0, 255, 0),
  matrix.Color(0, 0, 255),
  matrix.Color(75, 0, 130),
  matrix.Color(238, 130, 238)
};

void setup() {
  delay(3000);
//  Serial.begin(9600); // uncomment to use Arduino Serial Monitor/Plotter
  matrix.begin(); // This initializes the NeoMatrix library.
  matrix.setBrightness(40); // for USB power consumption
  matrix.show(); // Initialize all LEDS to off
  pixels.begin(); // This initializes the NeoPixel library.
  pixels.setBrightness(40); // for USB power consumption
}

void loop() {
//  rainbowVolumeBars();
  moodLights(getMicData() * 700);
}

void rainbowVolumeBars() {
  matrix.fillScreen(0); // clear screen
  for (int i=0; i < NUM_ROWS; i++) {
    matrix.fillRect(0, i, getMicData() * NUM_COL, 1, rainbow_colors[i]);  // Syntax reference: matrix.fillRect(startX, startY, dx, dy, color);
  }
  matrix.show();
}

void moodLights(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < getMicData()*8; q++) {
      for (int i=0; i < pixels.numPixels(); i=i+3) {
        pixels.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      pixels.show();

      delay(wait);

      for (int i=0; i < pixels.numPixels(); i=i+3) {
        pixels.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

float getMicData() {
  // getMicData() returns a value between 0-1V
  unsigned long startMillis = millis();  // Start of sample window
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

  return(volts);
}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}


