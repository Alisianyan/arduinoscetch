#include <Thread.h>
const int IN1 = 2;
const int IN2 = 3;
const int ENA = 4;
const int ENB = 5;
const int IN3 = 6;
const int IN4 = 7;
int leds[] = {8, 9, 10, 11, 12};
int sizeOfLeds = sizeof(leds)/sizeof(leds)[0];
int const allMotors[] = {IN1, IN2, IN3, IN4};
int input=0;
int buzz=13; // Buzzer Pin

Thread buzzerThread = Thread();
Thread ledThread = Thread();
void setup() {
  for(int i=2;i<=12;i++){
    pinMode(i,OUTPUT);
  }
  ledThread.onRun(led);
  ledThread.setInterval(100);

  buzzerThread.onRun(buzzer);
  buzzerThread.setInterval(5);
}

/*boolean debounce(boolean last){                 //Function to solve the problem of button debouncing
  boolean current=digitalRead(2);
  if(last!=current)
    {
      delay(5);
      current=digitalRead(2);
    }
  return current;
} */
  
void loop() {
  if (ledThread.shouldRun()) {
    ledThread.run();
  }

  if (buzzerThread.shouldRun()) {
    buzzerThread.run();  
  }
}

void forward() {
  for (int i: allMotors) {
    digitalWrite(i, HIGH);
  }
}

void led() {
  static int i = 0;
  static int step = 0;
  if (step == 0) { 
    digitalWrite(leds[i], HIGH);
    step = 1;
  }else if (step == 1) {
    digitalWrite(leds[(i + 1) % sizeOfLeds], HIGH);
    step = 2;
  }else {
    digitalWrite(leds[i], LOW);
    step = 0;
    i= (i+1) % sizeOfLeds;
  }
  // delay
}

void buzzerUp() {
    for(int hz = 440; hz < 1000; hz+=25){
      tone(buzz, hz, 50);
      //delay 5
    }
}

void buzzerDown() {
  for(int hz = 1000; hz > 440; hz-=25){
    tone(buzz, hz, 50);
    //delay 5
  }
}

void buzzer() {         //This function produces the 1st siren sound with ON/OFF led transition.
  // Whoop up
  
  for(int hz = 440; hz < 1000; hz+=25){
    tone(buzz, hz, 50);
    delay(5);
  }
  // Whoop down
  for(int hz = 1000; hz > 440; hz-=25){
    tone(buzz, hz, 50);
    delay(5);
 }
}
