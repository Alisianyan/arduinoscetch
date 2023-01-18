#include <Adafruit_NeoPixel.h>

#define PIN 3   // input pin Neopixel is attached to

#define NUMPIXELS      12 // number of neopixels in strip

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 1000; // timing delay in milliseconds


void setup() {
  // Initialize the NeoPixel library.
  pixels.begin();
  pixels.setBrightness(30);
}

void loop() {

  for (int i=0; i < NUMPIXELS; i=i+1) {
    if (i%2 ==1 ){
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0, 250, 250));

    // This sends the updated pixel color to the hardware.
    pixels.show();
    }

    else {
     pixels.setPixelColor(i, pixels.Color(250, 250, 0));
     pixels.show();
      
      }
    // Delay for a period of time (in milliseconds).
    delay(delayval);
  }
}
