int isPulled = 0;
void setup() {
  // прерывание на D2 (UNO/NANO)
  attachInterrupt(digitalPinToInterrupt(2), myButt, CHANGE);
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  //nMode(2, INPUT_PULLUP);
}

volatile uint32_t debounce;
void myButt() {

  if (millis() - debounce >= 100 && digitalRead(2)) {
    debounce = millis();
	Serial.println(isPulled);
    isPulled = !isPulled;
    digitalWrite(13, isPulled);
  }
}
void loop() {
  delay(999999999);
}