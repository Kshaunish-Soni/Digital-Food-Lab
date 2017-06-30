#include <dht.h>
#define dataPin 8
#include <Time.h>
#include <TimeLib.h>
#include <Wire.h>

boolean once = false;
unsigned long pM = 0;
//Start Time -- needed for the light system and harvesting
int dayElapsed = 6;
int sYear = 2017;

//Target Time -- How much time has elapsed in light cycle
int timeElapsed = 0;

//Is it day or night
boolean isDay = true;

//Light Pin #'s
const int growthLight = 3;
unsigned long previousMillis = 0;
boolean isOn = true;
long interval = 7.2E7;    // light interval is 20 hrs 7.2E7

//Temperature Control Pin #'s
dht DHT;
const int coolerPin = 4;    // 1# = digital pin number cooler is hooked up to
const int ceramicHeater = 5; // 2# = digital pin number heater is hooked up to
float targetTemp = 65; // 65 deg F morning 55 deg F night

// Humidity Control
const int humidifier = 6; // digital pin humidifer is hooked up to

//Hydroponics & Pump Digital Pins
const int ultraTrig = 11;
const int ultraEcho = 10;
const int analogInPin = A1;
float sensorValue = 0;

const int waterPump = 7;
const int nutrient = 9;
long prevNutrientMillis = 0;
boolean onceToday = false;
boolean onceToday1 = false;

//Serial Data
int serialCount = 0;


void setup() {
  Serial.begin(9600);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  //Establish contact with Raspberry Pi
  establishContact();

  // Light Setup
  pinMode(growthLight, OUTPUT);
  digitalWrite(growthLight, HIGH);

  // Temperature Control Setup
  pinMode(coolerPin, OUTPUT);
  pinMode(ceramicHeater, OUTPUT);

  // Humidifier Setup
  pinMode(humidifier, OUTPUT);
  digitalWrite(humidifier, LOW); // default, humidifier is off
  // Initialize the Adafruit Humidity and Temp Sensor

  // Water and Nutrient Pump
  pinMode(ultraTrig, OUTPUT);
  pinMode(ultraEcho, INPUT);
  pinMode(waterPump, OUTPUT);
  pinMode(nutrient, OUTPUT);
  pinMode(analogInPin, INPUT);

}

void loop() {
  cerealloop();
  tempControlLoop();
  lightControlLoop();
  //getWaterDepthNew();
  hydroponicsLoop();
  humidityCheck();
  nutrientLoop();
}

void cerealloop() {
  unsigned long currentMillis = millis();
  if (currentMillis - pM >= 1000 || !once) {
    Serial.flush();
    if (Serial.available() > 0) {
      if (!once) {
        int read1 = Serial.parseInt();
        delay(1000);
        Serial.flush();
        int read2 = Serial.parseInt();
        Serial.print(read2);
        int timeArray[4];
        float myData = read1;
        for (int i = 0; i < 4; i++) {
          timeArray[3 - i] = ((int)myData) % 100;
          myData /= 100;
        }
        dayElapsed = read2;
        if (dayElapsed % 6 != 0 ) {
          onceToday = true;
          onceToday1 = true;
        }
        setTime(timeArray[2], timeArray[3], 0, timeArray[1], timeArray[0], sYear);
        once = true;
      }

  
      Serial.print(getMainTemp());
      Serial.print(getTemp2());
      Serial.print(getBoxHumidity());
      Serial.print(getWaterDepthNew());
      Serial.print(".");
      Serial.println(dayElapsed);
      //Serial.print(hours());
    }
    Serial.flush();
  }
}

void timeLoop() {
  if (millis() % (long)864E5 == 0) {
    dayElapsed++;
    onceToday = false;
    onceToday1 = false;
  }
}

void tempControlLoop() {
  int tempValue = getMainTemp();
  //Cooler and Heater are Digital (On or Off)
  if (tempValue >= targetTemp - 5 && tempValue <= targetTemp + 5) {
    digitalWrite(coolerPin, LOW);    // default, cooler should be off
    digitalWrite(ceramicHeater, LOW);  // default heater should be off
  } else { //Will heat up to the targetTemp regardless of 5 deg threshold
    if (tempValue < targetTemp - 5) // min temp
    {
      digitalWrite(ceramicHeater, HIGH);   // turn on heater
    }
    else if (tempValue > targetTemp) // max temp
    {
      digitalWrite(coolerPin, HIGH);   // turn on cooler
    }
  }
}

void lightControlLoop() {
  unsigned long currentMillis = millis();
  //LIGHT CONTROL. Author: Anya Li. Edited by: Stone Mao
  if (dayElapsed > 3) {
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      if (interval >= 7.2E7) {
        interval = 1.44E7;  // light interval is 4 hours 1.44E7
        isOn = false;
        targetTemp = targetTemp - 10;
        digitalWrite(growthLight, LOW);
      }
      else {
        interval = 7.2E7;
        targetTemp = targetTemp + 10;
        isOn = true;
        digitalWrite(growthLight, HIGH);
      }
    }
  }
}

//void hydroponicsLoop() {
//  int level = 2;
//  int waterDepth = getWaterDepthNew();
//    //Serial.println(waterDepth);
//  if(waterDepth < 600){
//    digitalWrite(waterPump, HIGH);
//  } else {
//       digitalWrite(waterPump, LOW);
//  }
//}

//void hydroponicsLoop() {
//  int level = 45.25;
//  float waterDepth = getWaterDepth();
//  Serial.println(waterDepth);
//
//   sensorValue = analogRead(analogInPin);
//  //map it to the range of the analog out:
//  //outputValue = map(sensorValue, 0, 1023, 0, 255);
//  // change the analog out value:
//  //analogWrite(analogOutPin, outputValue);
//
//  // print the results to the serial monitor:
//  Serial.print("sensor = ");
//  Serial.print(sensorValue / 10);
//  
//  if (sensorValue/10 <= 85) {
//    digitalWrite(waterPump, HIGH);
//  } else {
//    digitalWrite(waterPump, LOW);
//  }
//}

// Controls humidity of Farm. Author: Anya Li. Edited by: Stone Mao
void humidityCheck() {
  int humidityValue = getBoxHumidity();

  if (humidityValue < 65.00) {
    digitalWrite(humidifier, HIGH);  // turn humidifier on if humidity is below 65%
  }
  else if (humidityValue >= 67.00)
  {
    digitalWrite(humidifier, LOW);  // turn humidifier off if humidity is greater or equal to 67%
  }
}

void nutrientLoop() {
  unsigned long currentMillis = millis(); //1000
  if (dayElapsed % 6 == 0 && !onceToday) { // If day is factor of 6 and hasn't turned on today
    if (!onceToday1) { // If prev mill hasn't turned on
      prevNutrientMillis = millis(); //Store starting prevMillisecond
      digitalWrite(nutrient, HIGH); // Turn pump on
      onceToday1 = true; // Set it to true so it does this if statement once
      //Serial.println("*");
    }
    if (currentMillis - prevNutrientMillis >= 12000) { // If the difference is more than 12 sec
      digitalWrite(nutrient, LOW); // Turn pump off
      onceToday = true; // Once today is true
    } else {
      digitalWrite(nutrient, HIGH);
    }
    //Serial.print("CurrentMillis: "); Serial.println(currentMillis);
    //Serial.print("Prev: "); Serial.println(prevNutrientMillis);
    //Serial.print("Difference: "); Serial.println(currentMillis - prevNutrientMillis);
  }
  //Serial.print("Once Today: "); Serial.println(onceToday);
}

//Serial Connection handshake
void establishContact() {
  while (Serial.available() <= 0) { // If not established
    Serial.print("A"); // Will send A
    delay(200);
  }
}

//INSTANCE METHODS
float getMainTemp() { // For main temperature sensorz
  int readData = DHT.read22(dataPin);
  int faren = (DHT.temperature * 9 / 5 + 28.5);
  //Serial.print("Temp: "); Serial.println(faren);
  return faren;
}

float getTemp2() {
  return 67;
}

float getBoxHumidity() {
  //Serial.print("Humidity: ");Serial.println(DHT.humidity);
  return DHT.humidity;
}

float getWaterDepthNew() {
  sensorValue = analogRead(analogInPin);
  Serial.print(sensorValue);
  return sensorValue;
}
//float getWaterDepth() {
//  digitalWrite(ultraTrig,LOW);
//  delayMicroseconds(2);
//  digitalWrite(ultraTrig, HIGH);
//  delayMicroseconds(10);
//  digitalWrite(ultraTrig, LOW);
//  int duration = pulseIn(ultraEcho, HIGH);
//
//  return 0.034*duration/2;
//}
