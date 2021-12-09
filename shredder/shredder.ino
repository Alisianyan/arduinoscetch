#define debounce 50
#define enginePin 6
#define relayPin 7
#define idleLevel 100
#define SClevel 800

unsigned long timeOfSCBegin = 0;
unsigned long relayTime = 0;
unsigned long timeOfLastPull = 0;
unsigned long timeOfLastAskIdle = 0;
unsigned long timeOfLastAskSC = 0;
bool isForward = true;

void setup() {
  pinMode(enginePin, OUTPUT);
  pinMode(relayPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  turnOnMotor();
}

void turnOnMotor() {
  if ((unsigned long)(millis() - timeOfLastPull) >= debounce && digitalRead(2) == HIGH && isForward == true) {    
    timeOfLastPull = millis();
    digitalWrite(enginePin, HIGH);
  }

  if ((unsigned long)(millis() - timeOfLastAskIdle) > 100) {
    timeOfLastAskIdle=millis();
    if (analogRead(A0) < idleLevel) {
      if (isForward) {
        digitalWrite(enginePin, LOW);
      }else {
        digitalWrite(enginePin, LOW);
        digitalWrite(relayPin, LOW);
        isForward = true;
      }
    }     
  }
  
  if ( (unsigned long)(millis() - timeOfLastAskSC) > 100) {
    timeOfLastAskSC = millis();
    if (analogRead(A0) > SClevel) {
      if (timeOfSCBegin == 0) {
        timeOfSCBegin = millis();
      }
    }else {
      timeOfSCBegin = 0;
    }
  }
  
  
  if (timeOfSCBegin != 0 && (unsigned long)(millis() - timeOfSCBegin) > 2000) {
    if (isForward) {
      digitalWrite(enginePin, LOW);
      digitalWrite(relayPin, HIGH);
      timeOfSCBegin = 0;
      relayTime = millis();
      isForward = false;
    }else {
      // что делать, если заклинило на пкти назад
      
    }
  }
  
  if (relayTime != 0 && (unsigned long)(millis() - relayTime) > 400) {
    digitalWrite(enginePin, HIGH);
    relayTime = 0;
  }
  Serial.println(analogRead(A0));
}
