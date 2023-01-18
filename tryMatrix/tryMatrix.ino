#include <Adafruit_NeoPixel.h>

#define PIN 2   // input pin Neopixel is attached to

#define NUMPIXELS      256 // number of neopixels in strip

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 1000; // timing delay in milliseconds
int arrayOfCoordinates [256][2];

void setup() {
  // Initialize the NeoPixel library.
  pixels.begin();
  pixels.setBrightness(10);
}

void loop() {

for (int j=0; j <= NUMPIXELS; j++){
    for (int k=0; k <= 2; k++){
        tempX
        tempY
        arrayOfCoordinates [j][k]
      }
  }

  for (int i=0; i <= NUMPIXELS + 4; i++) {

    pixels.setPixelColor(i, pixels.Color(255, 0, 0));
    pixels.show();
    
    pixels.setPixelColor(i-5, pixels.Color(0, 0, 0));
    pixels.show();      

    delay(delayval);
        digitalWrite(PIN, LOW);
  }
}
