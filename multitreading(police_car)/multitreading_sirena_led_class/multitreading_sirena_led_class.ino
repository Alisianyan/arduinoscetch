
int frequency = 400;
int frequencyIncrement = 25;
int maxFrequency = 1000;
int minFrequency = 440;
long buzzTimeOfLastAction = 0;
int frequencyStep = 50;
class Flasher
{
  // Class Member Variables
  // These are initialized at startup
  int ledPin;      // the number of the LED pin
  long OnTime;     // milliseconds of on-time
  long OffTime;    // milliseconds of off-time

  // These maintain the current state
  int ledState;                 // ledState used to set the LED
  unsigned long previousMillis;   // will store last time LED was updated

  // Constructor - creates a Flasher 
  // and initializes the member variables and state
  public:
  Flasher(int pin, long on, long off)
  {
  ledPin = pin;
  pinMode(ledPin, OUTPUT);     
    
  OnTime = on;
  OffTime = off;
  
  ledState = LOW; 
  previousMillis = 0;
  }

  void Update()
  {
    // check to see if it's time to change the state of the LED
    unsigned long currentMillis = millis();
     
    if((ledState == HIGH) && (currentMillis - previousMillis >= OnTime))
    {
      ledState = LOW;  // Turn it off
      previousMillis = currentMillis;  // Remember the time
      digitalWrite(ledPin, ledState);  // Update the actual LED
    }
    else if ((ledState == LOW) && (currentMillis - previousMillis >= OffTime))
    {
      ledState = HIGH;  // turn it on
      previousMillis = currentMillis;   // Remember the time
      digitalWrite(ledPin, ledState);   // Update the actual LED
    }
  }
};

 
Flasher led1(8, 123, 400);
Flasher led2(9, 350, 350);

 
void setup() 
{ 

} 
 
 
void loop() 
{ 
  
  led1.Update();
  led2.Update();
  
   if (millis() - buzzTimeOfLastAction > frequencyStep){
    tone(13, frequency, 50);
    frequency = frequency + frequencyIncrement;
    buzzTimeOfLastAction = millis();  
  }
  
  if (frequency >= maxFrequency) {
    frequencyIncrement = -25;
  }
  else if (frequency <= minFrequency) {
    frequencyIncrement = 25;
  } 
  
  digitalWrite(3, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(6, LOW);
  
}
