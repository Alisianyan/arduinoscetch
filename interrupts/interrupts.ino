#define LED_PIN 8
#define BTN_PIN 2
volatile int led_state = 0;
volatile int last_btn = 1;
void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT);
  pinMode(BTN_PIN, INPUT_PULLUP);
  last_btn = digitalRead(BTN_PIN);
  attachInterrupt(digitalPinToInterrupt(BTN_PIN), btnIsr, RISING);
}

void loop() {
  // put your main code here, to run repeatedly:
  int now = digitalRead(BTN_PIN);
  if (now != last_btn && == LOW){
    led_state = !led_state;
    digitalWrite(LED_PIN, led_state ? HIGH : LOW);
      last_btn=now;
    }
}

void btnIsr(void){
  led_state=!led_state;
  digitalWrite(LED_PIN, led_state ? HIGH : LOW);
  }
