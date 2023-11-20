class RGBled { //объявление класса
	int redPin; //поле класса
    //1. нету остальных цветов. беда
  	
  	public:
  	RGBled(int red) { // это конструктор 
    	redPin = red; //при создании объекта мы передаём три числа. Это первое
  		//2. и тут нету цветов. надо дописать?	
    }
  
  void ledUpDown(int pin) { //метод
    for (int i=0; i<=255; i++){
    	analogWrite(pin, i);
      	delay(2);
    }
    for (int i=255; i>=0; i--){
    	analogWrite(pin, i);
    	delay(2);
    }
  }
  
  //3. а вот здесь можно довисать функцию red_to_blue_to_green
  
};

// пример созадния объекта RGBled firstLed(13,12,8);
//4. допиши здесь создание своего объекта

void setup()
{
  for (int i=2; i<=12; i++){
  	pinMode(i, OUTPUT);
  }
}

void loop()
{

//не работает. надо написать функцию red_to_blue_to_green
  secondLed.red_to_blue_to_green();
  forthLed.red_to_blue_to_green();
}