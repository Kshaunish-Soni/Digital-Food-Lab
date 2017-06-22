int tempValue = 0;
const int tempPin = #;   // # = digital pin number temp sensor is hooked up to
const int coolerPin = 1#;    // 1# = digital pin number cooler is hooked up to
const int ceramicHeater = 2#; // 2# = digital pin number heater is hooked up to
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(tempPin, INPUT);
  pinMode(coolerPin, OUTPUT);
  pinMode(ceramicHeater, OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
    digitalWrite(coolerPin, LOW);    // default, cooler should be off
    digitalWrite(ceramicHeater, LOW);  // default heater should be off
    tempValue = digitalRead(tempPin);   
    Serial.print(" tempValue: ");
    if (tempValue <= 60.00)  // min temp
    {
      pinMode(ceramicHeater, HIGH);   // turn on heater
    }
    else if (tempValue >=65.00)   // max temp
    {
      pinMode(coolerPin, HIGH);   // turn on cooler
    }
    
    delay(60000);    // wait 1 minute
    
    if (tempValue <= 65.00)
    {
      pinMode(coolerPin, LOW);    // turn off cooler
    }
    else if (tempValue >=60.00)
    {
      pinMode(ceramicHeater, LOW);   // turn off heater
    }
    
}
