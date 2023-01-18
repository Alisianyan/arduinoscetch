#include <Adafruit_NeoPixel.h>

#define PIN 2   // input pin Neopixel is attached to

#define NUMPIXELS      256 // number of neopixels in strip

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 300; // timing delay in milliseconds


void setup() {
  // Initialize the NeoPixel library.
  pixels.begin();
  pixels.setBrightness(10);
}

void set(int x, int y, uint32_t color) {
  if (x >= 16 || y >= 16) return;
  if (y % 2 != 0) x = 15 - x;
  pixels.setPixelColor(y*16 + x, color);
}

#define EBOBA_SIZE 49

int eboba[ EBOBA_SIZE ][ 2 ] = { { 0, 0 }, { 0, 1 }, {1, 0}, {2, 0}, {0, 2},
                          {1, 2}, {2, 2}, {0, 3}, {0, 4}, {1, 4}, {2, 4},
                          {4, 0}, {4, 1}, {4, 2}, {4, 3}, {4, 4}, 
                          {5, 0}, {6, 1}, {5, 2}, {5, 4}, {6, 4},
                          {8, 1}, {8, 2}, {8, 3}, {9, 0}, {9, 4},
                          {10, 1}, {10, 2}, {10, 3},
                          {4+8, 0}, {4+8, 1}, {4+8, 2}, {4+8, 3}, {4+8, 4}, 
                          {5+8, 0}, {6+8, 1}, {5+8, 2}, {5+8, 4}, {6+8, 4},
                          {16, 0}, {16, 1}, {16, 2}, {16, 3}, {17, 4},
                          {18, 3}, {18, 2}, {17, 2}, {18, 1}, {18, 0}};

void showEboba() {
  static int c = 0;
  static int textOffset = 0;
  pixels.clear();
  textOffset = (textOffset + 1) % 20;
  c = (c + 1) % 256;
  uint32_t color = pixels.Color(255 - c, (c * 37) % 256, c);
  //uint32_t  color = pixels.Color(0, 255, 255);
  for (size_t i = 0; i < EBOBA_SIZE; i++) {
    set((eboba[i][0] + 20 - textOffset) % 24, eboba[i][1], color);
    //setGrad((eboba[i][0] + 20 - textOffset) % 24, eboba[i][1], c);
  }

  pixels.show();
  delay(delayval);
}

void showRandom() {
  for (size_t i = 0; i < 16; i++) {
      for (size_t j = 0; j < 16; j++) {
        set(i, j, pixels.Color(random(0, 256), random(0, 256), random(0, 256)));
      }
  }
  pixels.show();
}

void showGradient() {
  static int tick = 0;
  static int incr = 1;
  tick += incr;
  if (tick == 110) {
    incr = -1;
  }else if (tick == 0) {
    incr = 1;
  }
  for (size_t i = 0; i < 16; i++) {
      for (size_t j = 0; j < 16; j++) {
        int g = (i+j)*8 + tick;
        if (g >= 256) g = 255;
        if (g < 0) g = 0;
        int b = 255 - g;
        set(i, j, pixels.Color(0, g, b));
      }
  }
  pixels.show();
  delay(20);
}



void showCircles() {
  static int x1 = 7;
  static int y1 = 7;
  static int x2 = 7;
  static int y2 = 7;
  static int x3 = 7;
  static int y3 = 7;

  x1 += random(0, 3) - 1;
  y1 += random(0, 3) - 1;
  x2 += random(0, 3) - 1;
  y2 += random(0, 3) - 1;
  x3 += random(0, 3) - 1;
  y3 += random(0, 3) - 1;
  if (x1 >= 16) x1 = 15;
  if (x1 < 0) x1 = 0;
  if (x2 >= 16) x2 = 15;
  if (x2 < 0) x2 = 0;
  if (x3 >= 16) x3 = 15;
  if (x3 < 0) x3 = 0;
  if (y1 >= 16) y1 = 15;
  if (y1 < 0) y1 = 0;
  if (y2 >= 16) y2 = 15;
  if (y2 < 0) y2 = 0;
  if (y3 >= 16) y3 = 15;
  if (y3 < 0) y3 = 0;
  
  for (size_t i = 0; i < 16; i++) {
      for (size_t j = 0; j < 16; j++) {
          int r = (int)sqrt((i - x1)*(i - x1) + (j - y1)*(j - y1));
          int g = (int)sqrt((i - x2)*(i - x2) + (j - y2)*(j - y2));
          int b = (int)sqrt((i - x3)*(i - x3) + (j - y3)*(j - y3));
          if (r >= 256) r = 255;
          if (g >= 256) g = 255;
          if (b >= 256) b = 255;
          set(i, j, pixels.Color(int(255.0/(1+r)), int(255.0/(1+g)), int(255.0/(1+b))));
      }
  }

  pixels.show();
  delay(20);
}

void loop() {
  showCircles();
}
