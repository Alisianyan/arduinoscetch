#include <Adafruit_NeoPixel.h>

#define PIN 2   // input pin Neopixel is attached to

#define NUMPIXELS      256 // number of neopixels in strip

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 50; // timing delay in milliseconds
int arrayOfCoordinates [256][2];

void setup() {
  // Initialize the NeoPixel library.
  pixels.begin();
  pixels.setBrightness(10);
}

void loop() {

/*for (int j=0; j <= NUMPIXELS; j++){
    for (int k=0; k <= 2; k++){
        tempX
        tempY
        arrayOfCoordinates [j][k]
      }
  } */

  for (int i=0; i<=15; i++) {
      for (int k=0; k <= 15; k++) {
    pixels.setPixelColor((i*16)+k, pixels.Color(255-(16*i), 0, 0+(16*i)));
    pixels.show();
    //pixels.setPixelColor((i*16)+k, pixels.Color(255-(16*i), 0, 255-(16*i)));
    pixels.show();
    
    //pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    //pixels.show();      

    delay(delayval);
      }
  }
  digitalWrite(PIN, LOW);
}