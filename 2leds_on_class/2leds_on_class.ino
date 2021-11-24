const int IN1 = 2;
const int IN2 = 3;
const int ENA = 4;
const int ENB = 5;
const int IN3 = 6;
const int IN4 = 7;

//int leds[] = {8, 9, 10, 11, 12};
//int sizeOfLeds = sizeof(leds)/sizeof(leds)[0];
int const allMotors[] = {IN1, IN2, IN3, IN4};
int input=0;
int buzz=13;
long buzzerInterval = 5;

class Flasher {
  int ledPin;
  int ledState;
  long ledOnTime;
  long ledOffTime;
  long ledTimeOfLastAction;
  
  public:
  Flasher(int ledPin, long ledOnTime, long ledOffTime){
    this->ledPin = ledPin;
    this->ledOnTime = ledOnTime;
    this->ledOffTime = ledOffTime;
    this->ledState = LOW;
    this->ledTimeOfLastAction = 0;
  }
  
  
  void update(long currentMillis) {    
    if ((this->ledState == HIGH) && (currentMillis - this->ledTimeOfLastAction > this->ledOnTime)){
      this->ledState = LOW;
      digitalWrite(this->ledPin, this->ledState);
      this->ledTimeOfLastAction = currentMillis;
    }
    if ((this->ledState == LOW) && (currentMillis - this->ledTimeOfLastAction > this->ledOffTime)){
      this->ledState = HIGH;    
      digitalWrite(this->ledPin, this->ledState);
      this->ledTimeOfLastAction = currentMillis;
    }
  } 
};


Flasher redLed(8, 2000, 1000); 
Flasher blueLed(9, 750, 250);


void setup() {
  for (int i=2; i<=13; i++){
    pinMode(i, OUTPUT);
  }
}
void loop() {
  unsigned long currentMillis = millis();
  redLed.update(currentMillis);
  blueLed.update(currentMillis);
}

//доработать
////
/////
/////
void one() {         //This function produces the 1st siren sound with ON/OFF led transition.
  // Whoop up
  for(int hz = 440; hz < 1000; hz+=25){
    tone(buzz, hz, 50);
    delay(5);
    for(int i=3;i<=7;i++)
    digitalWrite(i,HIGH);
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
