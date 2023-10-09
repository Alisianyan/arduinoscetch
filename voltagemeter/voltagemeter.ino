int sensorValue = 0;
float voltage = 0;
#include <Adafruit_NeoPixel.h>
#define PIN 3   // input pin Neopixel is attached to
#define NUMPIXELS      12 // number of neopixels in strip
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
void setup()
{
  pinMode(A0, INPUT);
  Serial.begin(9600);
  pixels.begin();
  pixels.setBrightness(50);
}

void loop()
{

  voltmeter();
  Serial.println(voltmeter());
  led_on(int(voltmeter()));
}

float voltmeter(){
  sensorValue = analogRead(A0);
  voltage = sensorValue*5/1023;
  return voltage;
}

void led_on(int num_leds){
    for (int i=0; i < num_leds; i=i+1) {
     pixels.setPixelColor(i, pixels.Color(250, 250, 0));
     pixels.show();
    delay(300);
  }
  }

  
