int sensorValue = 0;
float voltage = 0;
void setup()
{
  pinMode(A0, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

void loop()
{

  sensorValue = analogRead(A0);
  voltage = sensorValue*5/1023;
  Serial.println(voltage);
  delay(100);
}
