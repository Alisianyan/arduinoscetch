volatile boolean is_pressed= 0;
volatile boolean is_lightning= 0;
volatile unsigned long long when_pressed = 0;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(3, INPUT_PULLUP);///по умолчанию сигнал 1
attachInterrupt(1, myInterrupt, FALLING);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (is_pressed){
    if (millis()>300+when_pressed) {
      if (is_lightning==0) {
//        Serial.println(ltos(when_pressed));
        is_lightning=true;
        digitalWrite(13, HIGH);
      } else if (is_lightning==1) {
        is_lightning=false;
        digitalWrite(13, LOW);
      }
      when_pressed = millis();
    }
    is_pressed=0;
  }
}

void myInterrupt(){
  is_pressed=1;
}
