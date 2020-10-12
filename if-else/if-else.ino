void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  int ports[] = {2, 5, 6};
  for (int i = 0; i <3; i++) {
      digitalWrite(ports[i], LOW);
    }
  // put your main code here, to run repeatedly:
  int sensorValue = analogRead(A0);
  Serial.println(sensorValue);

  if (sensorValue < 300) {
    digitalWrite(2, HIGH);
    } 
  else if (sensorValue < 700) {
    digitalWrite(5, HIGH);
  }
  else {
    digitalWrite(6, HIGH);
    }
          delay(100);
}
