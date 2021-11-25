bool isPulled = false;
void setup() {
  // прерывание на D2 (UNO/NANO)
  attachInterrupt(0, isr, CHANGE);
  Serial.begin(9600);
  //nMode(2, INPUT_PULLUP);
}

volatile uint32_t debounce;
void isr() {

  if (millis() - debounce >= 100 && digitalRead(2)) {
    debounce = millis();
	Serial.println(isPulled);
    isPulled = !isPulled;
  }
}
void loop() {
  delay(999999999);
}