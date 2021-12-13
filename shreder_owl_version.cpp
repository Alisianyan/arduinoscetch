#define debounce 50 //при переключении кнопки есть явление дребезга - показания скачут от 0 к 1
// задержка в 50мс - проверяем, что через 50мс значение не изменилось
#define buttonPin 2
#define enginePin 6
#define relayPin 7
#define idleLevel 100
#define SClevel 800
#define CURRENT_SENSOR_PIN A0

#define AVG_ARRAY_SIZE 50 //для метода getAverage - для скольки последних значений считаем среднее арифметическое

//возвращает averageValue/AVG_ARRAY_SIZE - среднее значение датчика тока за 50мс
class Average {
	int analogValues[AVG_ARRAY_SIZE];
	int index = 0;
	int averageValue;
	
	Average() {
		memset(analogValues, 0, sizeof(analogValues));
	}
	
	int getAverage() {
		for (int i=1; i<AVG_ARRAY_SIZE; i++){
			analogValues[i-1] = analogValues[i];
		}
		analogValues[AVG_ARRAY_SIZE] = analogRead(CURRENT_SENSOR_PIN);
		
		int sum = 0;
		for (int i=0; i<AVG_ARRAY_SIZE; i++){
			sum += analogValues[i]
		}
		
		return averageValue/AVG_ARRAY_SIZE;
	}
	
};

//возможные состояния шредера
//READY - мотор стоит, ждём крышечки
//FORWARD - жуём крышечку. Мотор едет вперёд
//CHEW - короткое замыкание при вращении мотора вперёд
//RELAY_REVERCE - переключаем реле
//BACKWARD_DRIVE - едем назад
//EBOBA - короткое замыкание при движении назад
enum {READY = 0, FORWARD, CHEW, RELAY_REVERCE, BACKWARD_DRIVE, EBOBA};

int state = READY;
int previousCheckTime = 0; //проверка кнопки

void shreder_programm() {
  switch (state) {
    case READY: {
      if ((unsigned long)(millis() - previousCheckTime) >= debounce && digitalRead(buttonPin) == LOW) {     //если кнока нажата && устранили дребезг &&мотор не работал
        previousCheckTime = millis();
        digitalWrite(enginePin, HIGH); //включаем мотор
        state = FORWARD; //состояние - едем вперёд
      }
    }break;
    case FORWARD: { 
      if ((unsigned long)(millis() - previousCheckTime) >= debounce) {
      	previousCheckTime = millis(); 
        int current = analogRead(A0); //current - показания датчика тока
        if (current < idleLevel) { //если двигатель работает вхолостую
        	digitalWrite(enginePin, LOW); //выключаем мотор
        	state = READY; //переходим в состояние "мотор выключен, ждём крышечку"
        }else if (current >= SClevel) { //если ток больше уровня короткого замыкания
        	state = CHEW; //переходим в состояние короткое замыкание при вращении мотора вперёд
        }
      }
    }break;
    case CHEW: { //короткое замыкание при вращении мотора вперёд
      if ((unsigned long)(millis() - previousCheckTime) >= debounce) {
      	int current = analogRead(A0);
        if (current < SClevel) {
        	state = FORWARD;
          	previousCheckTime = millis();
        }else if (millis() - previousCheckTime > 2000) { //если КЗ больше 2 секунд
        	state = RELAY_REVERCE; //переходим в состояние "переключаем реле"
          	digitalWrite(enginePin, LOW);
      		digitalWrite(relayPin, HIGH);
          	previousCheckTime = millis(); //обнуляем время последней проверки датчика, чтобы выйти из этого условия
          	delay(400);
          	state = BACKWARD_DRIVE; //переходим в состояние "едем назад"
          	digitalWrite(enginePin, HIGH);
        }
      }
    }break;
    case BACKWARD_DRIVE: { //если состояние "едем назад"
    	if ((unsigned long)(millis() - previousCheckTime) >= debounce) {
			previousCheckTime = millis(); //проверяем, что прошло время дебаунса
			int current = analogRead(A0); 
			if (current < idleLevel) {
				digitalWrite(enginePin, LOW);
				digitalWrite(relayPin, LOW);
				state = READY;
            }else if (current > SClevel) {
            	digitalWrite(enginePin, LOW);
				digitalWrite(relayPin, LOW);
              	state = EBOBA;
            }
		}
    }break;
    case EBOBA: {
		// режим КЗ на реверсе
		digitalWrite(LED_BUILTIN, HIGH);
    }break;
  }
}

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(enginePin, OUTPUT);
  pinMode(relayPin, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  shreder_programm();
}