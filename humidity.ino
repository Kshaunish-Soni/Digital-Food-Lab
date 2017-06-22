int humidityValue = 0;
const int humiditySensor = #;  // digital pin humidity sensor is hooked up to
const int humidifier = #; // digital pin humidifer is hooked up to

void setup() {
  pinMode(humiditySensor, INPUT);
  pinMode(humidifer, OUTPUT);
  digitalWrite(humidifier, LOW);  // default, humidifier is off
}

void loop () {
  humidityValue = digitalRead(humiditySensor);
  Serial.print(humidityValue + "%");
  if (humidityValue < 65.00)
  {
    digitalWrite(humidifer, HIGH);  // turn humidifier on if humidity is below 65%
  }
  
  else if (humidityValue >= 67.00)
  {
    digitalWrite(humidifier, LOW);  // turn humidifier off if humidity is greater or equal to 67%
  }
  
  delay(10000);   // check every 10 seconds
}

