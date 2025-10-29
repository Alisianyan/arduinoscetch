int PWM_pins[] = {2, 13, 14, 15, 16, 38, 39, 40, 41, 42};
void setup() {
  // put your setup code here, to run once:
    for(auto pin : PWM_pins) {
      pinMode(pin, OUTPUT);;
    }
}

void loop() {
   for (int i = 0; i < 150; i++) {
      for(auto pin : PWM_pins) {
          analogWrite(pin, i);
          delay(1);
        }
    }
}
