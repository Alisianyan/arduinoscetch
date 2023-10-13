// C++ code
//
int moisture = 0;

void setup()
{
  pinMode(A1, INPUT);
  Serial.begin(9600);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
}

void loop()
{
  led_off();
      
  moisture = analogRead(A1);
  Serial.println(moisture);
  which_led_turn_on();
  delay(100); // Wait for 100 millisecond(s)
}

void led_off() {
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
}

void which_led_turn_on () {
    if (moisture < 200) {
    digitalWrite(12, HIGH);
  } else {
    if (moisture < 400) {
      digitalWrite(11, HIGH);
    } else {
      if (moisture < 600) {
        digitalWrite(10, HIGH);
      } else {
        if (moisture < 800) {
          digitalWrite(9, HIGH);
        } else {
          digitalWrite(8, HIGH);
        }
      }
    }
  }
}
