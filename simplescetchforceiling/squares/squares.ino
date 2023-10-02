#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwms[4]; //4 шим-контроллера лент
//каждому квадрату на потолке - свой экземпляр
class Square{
  public: //чтобы можно было достучаться до полей класса
  Adafruit_PWMServoDriver* pwmController; //указатель на контроллер нужен чтобы экземпляр контроллера был создан единожды и более не изменялся
  unsigned int pwmRedPort;
  unsigned int pwmGreenPort;
  unsigned int pwmBluePort;
};

Square squares[4][5];

void setup() {
  Serial.begin(9600);
  Wire.setClock(400000);
  
  pwms[0]=Adafruit_PWMServoDriver(0x40);
  pwms[1]=Adafruit_PWMServoDriver(0x41, Wire);
  pwms[2]=Adafruit_PWMServoDriver(0x16, Wire);
  pwms[3]=Adafruit_PWMServoDriver(0x70, Wire);
  for (int i = 0; i<=3; i++){
    pwms[i].begin();
    pwms[i].setOscillatorFrequency(27000000);
    pwms[i].setPWMFreq(1600);
  }

  for (int i = 0; i<=3; i++){
    for (int k = 0; k <= 4; k++){
      squares[i][k].pwmController=&pwms[i]; //см выше - pwms это массив pwmController, у них указатель
      squares[i][k].pwmRedPort=3*k;
      squares[i][k].pwmGreenPort=3*k+1;
      squares[i][k].pwmBluePort=3*k+2;
    }
  }
}

void setColorbyXY(uint32_t red, uint32_t green, uint32_t blue, uint32_t indexX, uint32_t indexY){
  Adafruit_PWMServoDriver* pwm = squares[indexX][indexY].pwmController; //мы далее 3 раза обращаемся к pwm. мы хотим обращаться к области памяти, а не присваивать
  /*setPWM принимает 3 аргумента (номер порта, начальное положение, конечное положение) 
   номер порта мы узнаём по координатам XY по squares[indexX][indexY].pwmRedPort
   max для начального/конечного положения - 4095. мы приводим rgb(255, 255, 255) к виду (4095, 4095, 4095)
  */
  pwm->setPWM(squares[indexX][indexY].pwmRedPort, 0, red*16); //поскольку pwm - указатель, то при вызове функции нужна -> это  как (*pwm).setPWM()
  pwm->setPWM(squares[indexX][indexY].pwmGreenPort, 0, green*16);
  pwm->setPWM(squares[indexX][indexY].pwmBluePort, 0, blue*16);

 /* int a = 5;
  int* b = &a;

   (*b)  a
   (*b).foo()   a.foo()
   b->foo()*/
}
void gradientUpdate(uint32_t indexX, uint32_t indexY){
  unsigned long currentMillis = millis();
  unsigned long previousMillis=0;
  unsigned long millisofLastAction =0;
  int increment = 10;
  int addColor = 0; 
  if (millis() - millisofLastAction > 5){
      setColorbyXY(increment, 255-increment, 0, indexX, indexY);
      millisofLastAction = millis();
      addColor = addColor + increment;
  }
  if (increment <=255){
    increment=10;
  }  
  if (increment >255){
    increment = -10;
  }  
}
 
void loop() {
    for (int i = 0; i<=3; i++){
      for (int k = 0; k <= 4; k++){
        setColorbyXY(255, 255, 255, i, k);
        delay(2000);
      }
    }
    
} 
