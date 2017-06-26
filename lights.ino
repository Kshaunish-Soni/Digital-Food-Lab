int lights = 3;
unsigned long previousMillis = 0;
boolean isOn = true;
long interval = 7.2E7;    // light interval is 20 hrs 7.2E7
void setup() {
  Serial.begin(9600);
  pinMode(lights, OUTPUT);
  digitalWrite(lights, HIGH);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;
    if (interval == 7.2E7) {
      interval = 1.44E7;  // light interval is 4 hours 1.44E7
      isOn = false;
      digitalWrite(lights, LOW);
    }
    else {
      interval = 7.2E7;
      isOn = true;
      digitalWrite(lights, HIGH);
    }
  }
}
