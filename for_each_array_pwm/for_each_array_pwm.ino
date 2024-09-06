int PWM_pins[] = {2, 13, 14, 15, 16, 38, 39, 40, 41, 42};
void setup() {
  // put your setup code here, to run once:
    for(auto pin : PWM_pins) {
      pinMode(pin, OUTPUT);;
    }
}

void loop() {
  // put your main code here, to run repeatedly:
  for(auto pin : PWM_pins) {
      test_pwm (pin);
    }
}

void test_pwm (int pin) {
  for (int i = 0; i < 255; i++) {
    analogWrite(pin, i);
    delay(1);
  }
  delay(1000);
  for (int i = 255; i > 0; i--) {
    analogWrite(pin, i);
    delay(1);
  }
  delay(1000);
}
