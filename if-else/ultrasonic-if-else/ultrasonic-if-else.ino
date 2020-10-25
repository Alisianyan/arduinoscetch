int GREEN = 3;
int YELLOW = 4;
int RED = 5;

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

void setup()
{
  Serial.begin(9600);

}

void loop()
{
  int inches = 0;
  cm = 0.01723 * readUltrasonicDistance(7, 7);

  if (cm <= 30) {
  digitalWrite(GREEN, HIGH);
}
else if (cm <= 60) {
  digitalWrite(YELLOW, HIGH);
}
else {
  digitalWrite(RED, HIGH);
}
  
  delay(100); // Wait for 100 millisecond(s)
  digitalWrite(GREEN, LOW);  digitalWrite(YELLOW, LOW);  digitalWrite(RED, LOW);
}
