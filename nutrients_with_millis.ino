int nutrients = 7; 
unsigned long previousMillis = 0;
boolean isOn = true;
long interval = 12000; // nutrients pump on for 12 seconds
void setup() {
  Serial.begin(9600);
  pinMode(nutrients, OUTPUT);
  digitalWrite(nutrients, HIGH);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;
    if (interval == 12000) {
      interval = 5.184E8; // nothing for 6 days, basically pump nutrients every 6 days
      isOn = false;
      digitalWrite(nutrients, LOW);
    }
    else {
      interval = 12000;
      isOn = true;
      digitalWrite(nutrients, HIGH);
    }
  }
}

