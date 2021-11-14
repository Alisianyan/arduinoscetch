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

void setup() {
  for(int i=2;i<=12;i++){
    pinMode(i,OUTPUT);
  }
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
  for(int i=3;i<=12;i++){
    digitalWrite(i,LOW);
    one();
  } 
}

void forward() {
  for (int i: allMotors) {
    digitalWrite(i, HIGH);
  }
}

void led() {
  for (int i = 0; i < sizeOfLeds; i++) {
    digitalWrite(leds[i], HIGH);
    delay(100);
    digitalWrite(leds[(i + 1) % sizeOfLeds], HIGH);
    delay(100);
    digitalWrite(leds[i], LOW);
  }
}

void one() {         //This function produces the 1st siren sound with ON/OFF led transition.
  // Whoop up
  for(int hz = 440; hz < 1000; hz+=25){
    tone(buzz, hz, 50);
    delay(5);
    for(int i=3;i<=7;i++) {
      digitalWrite(i,HIGH);
    }
  }
  // Whoop down
  for(int hz = 1000; hz > 440; hz-=25){
    tone(buzz, hz, 50);
    delay(5);
    for(int i=3;i<=7;i++)
    {
      digitalWrite(i,LOW);
      digitalWrite(i+5,HIGH);
    }
 }
}
