int phValue = 0;
const int phSensor = #; // the digital pin the ph sensor is hooked up to
const int phUp = #;     // the digital pin the ph up pump is hooked up to 
const int phDown = #;   // the digital pin the ph down pump is hooked up to

void setup () {
  pinMode(phValue, INPUT);
  pinMode(phUp, OUTPUT);
  pinMode(phDown, OUTPUT);
  digitalWrite(phUp, LOW);  // default, the ph up pump is off
  digitalWrite(phDown, LOW);  // default the ph down pump is off
  
}

void loop () {
  phValue = digitalRead(phSensor);  // read the ph sensor
  Serial.print(phValue);            // show the ph value
  if (phValue < 5.80)             // if the ph is below 5.8, turn on the ph up pump
  {
    digitalWrite(phUp, HIGH);
  }

  else if (phValue > 6.00)      // if the ph is over 6.00, turn on the ph down pump
  {
    digitalWrite(phDown, HIGH);
  }

  delay(5000);   // wait for 5 seconds

  if (phValue >= 5.80)        // if the ph value is greater or equal to 5.8, turn off the ph up pump
  {
    digitalWrite(phUp, LOW);
  }

  else if (phValue < 6.00);   // if the ph value is less than 6.00, turn off the ph down pump
  {
    digitalWrite(phDown, LOW);
  }
 
}

