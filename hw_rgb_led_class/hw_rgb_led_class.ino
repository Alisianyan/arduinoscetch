class RGBled {
  int redPin;
    int bluePin;
    int greenPin;
    
    public:
    RGBled(int red, int blue, int green) {
      redPin = red;
      bluePin = blue;
      greenPin = green; 
    }
  
  void ledUpDown(int pin) {
    for (int i=0; i<=255; i++){
      analogWrite(pin, i);
        delay(2);
    }
    for (int i=255; i>=0; i--){
      analogWrite(pin, i);
      delay(2);
    }
  }
  
  void red_to_blue_to_green() {
    ledUpDown(redPin);
    ledUpDown(bluePin);
    ledUpDown(greenPin);
  }
};

RGBled firstLed(13,12,8);
RGBled secondLed(11,10,9);
RGBled thirdLed(7, 4, 2);
RGBled forthLed(6, 5, 3);

void setup()
{
  for (int i=2; i<=12; i++){
    pinMode(i, OUTPUT);
  }
}

void loop()
{
  secondLed.red_to_blue_to_green();
  forthLed.red_to_blue_to_green();
}
