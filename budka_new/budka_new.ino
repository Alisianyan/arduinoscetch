#include <Servo.h>

// defines variables
long duration;
int distance;
int motorSpeed = 3; // скорость мотора
int motorPin1 = 4; //контакт 1 мотора
int motorPin2 = 5; // контакт 2 мотора
int ledBrightness = 6;  // яркость светодиода
int ledPlus = 7; // плюс светодиодов
int ledMinus = 8; // минус светодиодов

int buttonPin = 2;

int lastIsForward = 1;
int isDown = 0;
//int buttonScore = 0;
int buttonState;

Servo servo;

void setup() {
//  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buttonPin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(motorSpeed, OUTPUT);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(ledBrightness, OUTPUT);
  pinMode(ledPlus, OUTPUT);
  pinMode(ledMinus, OUTPUT);
  servo.attach(9);
  Serial.begin(9600); // Starts the serial communication
}
void loop() {
//int buttonState=0;
delay(1000);
 buttonState=(digitalRead(buttonPin)); 
if ( buttonState == 1 && isDown == 0){
  //start led, start motor
    isDown = 1;
    if (lastIsForward) {
        integrator();
        sweep_paper();
        lastIsForward = 0;
    }
    else {
        integrator();
        unsweep_paper();
        lastIsForward = 1;
    }
}
   else {
//    buttonScore = 0;
    //stop led, stop motor
    turn_all_off();
    isDown = 0;
   }
}

void led_on() {
    analogWrite(ledBrightness, 255);
    digitalWrite(ledPlus, HIGH);
    digitalWrite(ledMinus, LOW);
  }

void sweep_paper() {
    analogWrite(motorSpeed, 100);
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
    delay(2000);
  }

void unsweep_paper() {
    analogWrite(motorSpeed, 100);
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, HIGH);
    delay(2000);
  }

void turn_all_off() {
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
    digitalWrite(ledPlus, LOW);
    digitalWrite(ledMinus, LOW);
  }

void integrator() {
  led_on(); 
  for (int i = 1; i<=6; i++){
    for (int pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
      servo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(2);                       // waits 15ms for the servo to reach the position
    }
    for (int pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      servo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(2); // waits 15ms for the servo to reach the position
    }
  }
}
