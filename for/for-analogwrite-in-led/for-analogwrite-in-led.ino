int LED = 3;
void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
}

void loop() {
  //плавно зажжём светодиод
  for (int i = 0; i <255; i++) {
  analogWrite(LED, i);
  delay(10);
    }

  //плавно выключим светодиод
  for (int i = 255; i > 0; i = i-1) {
  analogWrite(LED, i);
  delay(10);
    }
}
