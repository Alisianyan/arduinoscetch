#include <Adafruit_NeoPixel.h>
#define PIN 3
#define LED                         LED_BUILTIN  // digital pin connected to LED, for testing of switch code only
#define NUMPIXELS 100
bool    led_status  =                        LOW; // start with LED off, for testing of switch code  only

int     button_switch =                       2; // external interrupt  pin

#define switched                            true // value if the button  switch has been pressed
#define triggered                           true // controls  interrupt handler
#define interrupt_trigger_type            RISING // interrupt  triggered on a RISING input
#define debounce                              10  // time to wait in milli secs
Adafruit_NeoPixel strip = Adafruit_NeoPixel(300, PIN, NEO_GRB + NEO_KHZ800);
void turnOffStrip();
uint32_t Wheel(byte WheelPos);
void colorWipe(uint32_t c, uint8_t wait);
void rainbowCycle(uint8_t wait);
void rainbow(uint8_t wait);


volatile  bool interrupt_process_status = {
  !triggered                                     // start with no switch press pending,  ie false (!triggered)
};
bool initialisation_complete =            false;  // inhibit any interrupts until initialisation is complete

//
// ISR for  handling interrupt triggers arising from associated button switch
//
void  button_interrupt_handler()
{
  if (initialisation_complete == true)
  {  //  all variables are initialised so we are okay to continue to process this interrupt
    if (interrupt_process_status == !triggered) {
      // new interrupt so okay  start a new button read process -
      // now need to wait for button release  plus debounce period to elapse
      // this will be done in the button_read  function
      if (digitalRead(button_switch) == HIGH) {
        // button  pressed, so we can start the read on/off + debounce cycle wich will
        //  be completed by the button_read() function.
        interrupt_process_status  = triggered;  // keep this ISR 'quiet' until button read fully completed
      }
    }
  }
} // end of button_interrupt_handler

void setup() {
  Serial.begin(9600);
  strip.begin();
  strip.setBrightness(30); //adjust brightness here
  strip.show(); // Initialize all pixels to 'off'
  pinMode(LED, OUTPUT);
  pinMode(button_switch, INPUT);
  attachInterrupt(digitalPinToInterrupt(button_switch),
                  button_interrupt_handler,
                  interrupt_trigger_type);
  initialisation_complete = true; // open interrupt processing for business
}  // end of setup function

void loop() {
  // test buton switch and process  if pressed
  if (interrupt_process_status) {
    led_status = HIGH - led_status;  // toggle state
    interrupt_process_status = false;
    if (led_status == HIGH) {
      // button on/off cycle now  complete, so flip LED between HIGH and LOW
      Serial.println("Pushed");
      rainbowCycle(20);
      digitalWrite(LED, led_status);
    }else {
      turnOffStrip();
      Serial.println("pwn");
      // do  other things....
    }
  }
}
////////////////////Rainbow/////////
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(5);
  }
}
void rainbow(uint8_t wait) {
  uint16_t i, j;
 
  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}
// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;
 
  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
    if (interrupt_process_status) {
      return;
    }
  }
}
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
void turnOffStrip() {
    for (int i=0; i < NUMPIXELS; i=i+1) {
     strip.setPixelColor(i, strip.Color(250, 250, 0));
     strip.show();
  }
  while (true) {
    delay(100);
    if (interrupt_process_status) {
      return;
    }
  }
}
