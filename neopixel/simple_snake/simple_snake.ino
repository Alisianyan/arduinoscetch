#include <Adafruit_NeoPixel.h>

#define PIN 3	 // input pin Neopixel is attached to

#define NUMPIXELS      12 // number of neopixels in strip

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 500; // timing delay in milliseconds


void setup() {
  // Initialize the NeoPixel library.
  pixels.begin();
  pixels.setBrightness(10);
}

void loop() {


  for (int i=0; i <= NUMPIXELS + 4; i=i+2) {
    if (i % 2 ==0 )
    pixels.setPixelColor(i, pixels.Color(255-i*50, i*50, 0));
    pixels.show();
    
    pixels.setPixelColor(i-5, pixels.Color(0, 0, 0));
    pixels.show();    	

    delay(delayval);
        digitalWrite(PIN, LOW);
  }
}
