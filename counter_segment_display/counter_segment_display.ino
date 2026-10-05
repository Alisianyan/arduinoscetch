#include <GyverSegment.h>
volatile int counter = 0;
int tmr=0;
void isrUP(){
    if (isPushed(tmr, 2)) {
      counter++;
    }
}
void isrDOWN(){
  if (isPushed(tmr, 3)) {
    counter--;
  }
}

const uint8_t digs[] = {5, 13, 4};
const uint8_t segs[] = {6, 7, 8, 9, 10, 11, 12, 1};
DispBare<3, 1, false> disp(digs, segs);
void setup() {
   pinMode(3, INPUT_PULLUP);
   pinMode(2, INPUT_PULLUP);
   attachInterrupt(digitalPinToInterrupt(2), isrUP, FALLING);
   attachInterrupt(digitalPinToInterrupt(3), isrDOWN, FALLING);
}

void loop() {
   static uint32_t tmr;
   disp.clear();
   disp.setCursor(0);
   disp.print(counter);
   disp.update();
   disp.delay(20);
  disp.tick();
}

int isPushed (int& tmr, int pin){
  int state = digitalRead(pin);
  if (millis() - tmr >= 50 && state == 0) {
    tmr = millis(); 
    return 1;
  }
  return 0;
}
