int phValue = 0;
const int phSensor = #; 
const int phUp = #;
const int phDown = #;

void setup () {
  pinMode(phValue, INPUT);
  pinMode(phUp, OUTPUT);
  pinMode(phDown, OUTPUT);
  digitalWrite(phUp, LOW);
  digitalWrite(phDown, LOW);
  
}

void loop () {
  phValue = digitalRead(phSensor);
  Serial.print(phValue);
  if (phValue < 5.80)
  {
    digitalWrite(phUp, HIGH);
  }

  else if (phValue > 6.00)
  {
    digitalWrite(phDown, HIGH);
  }

  delay(5000);   // wait for 5 seconds

  if (phValue >= 5.80)
  {
    digitalWrite(phUp, LOW);
  }

  else if (phValue < 6.00);
  {
    digitalWrite(phDown, LOW);
  }
 
}

