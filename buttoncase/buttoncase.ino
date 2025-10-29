const int buttonPin = 2;     // Кнопка на пине D2
int mode = 0;                // Текущий режим
int lastButtonState = LOW;  // Предыдущее состояние кнопки
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;  // Задержка для антидребезга

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("starting");
}

void loop() {
  int reading = digitalRead(buttonPin);

  // Антидребезг: проверяем, что состояние стабильно
  if (reading != lastButtonState) {
    //Serial.println(millis());
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // Если кнопка нажата (т.к. подключена к GND)
    //Serial.println(millis());
    if (digitalRead(buttonPin) == HIGH && lastButtonState == LOW) {
      Serial.println("Button is down");
      lastButtonState == HIGH;
      mode++;
      doSwitchStatement();
      lastButtonState == LOW;
      if (mode > 2) mode = 0;{ // например, 3 режима 
      Serial.print("Switched to mode: ");}
      Serial.println(mode);
    }
  }
}
void doSwitchStatement() {
  switch(mode) {
  case 0:
    Serial.println("Case 0");
    // add a call to doExtraStuff() if you like
    break;
  case 1:
    Serial.println("Case 1");
    break;
  case 2:
    Serial.println("Case 2");
    break;
  case 3:
    Serial.println("You've reached the last selection.");
    Serial.println("Case 3");
  }
}