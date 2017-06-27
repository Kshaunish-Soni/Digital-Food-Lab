#include <dht.h>
#define dataPin 8
#include <Time.h>
#include <TimeLib.h>
#include <Wire.h>


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
const int waterDepthSensor = A0;
const int waterPump = 0;
const int nutrientPump = 7;

//Serial Data
int serialCount = 0;


void setup() {
  Serial.begin(9600);

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
  pinMode(waterDepthSensor, INPUT);
  pinMode(waterPump, OUTPUT);
  pinMode(nutrientPump, OUTPUT);
  
}

void loop() {
  tempControlLoop();
  lightControlLoop();
  hydroponicsLoop();
  humidityCheck();
}

void tempControlLoop() {
  int tempValue = getMainTemp();
  //Cooler and Heater are Digital (On or Off)
  if (tempValue >= targetTemp - 5 && tempValue <= targetTemp + 5) {
    digitalWrite(coolerPin, LOW);    // default, cooler should be off
    digitalWrite(ceramicHeater, LOW);  // default heater should be off
  } else { //Will heat up to the targetTemp regardless of 5 deg threshold
    if (tempValue < targetTemp) // min temp
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
  //LIGHT CONTROL
  if (currentMillis - previousMillis >= interval){
    previousMillis = currentMillis;
    if (interval == 7.2E7) {
      interval = 1.44E7;  // light interval is 4 hours 1.44E7
      isOn = false;
      digitalWrite(growthLight, LOW);
    }
    else {
      interval = 7.2E7;
      isOn = true;
      digitalWrite(growthLight, HIGH);
    }
  }
}

void hydroponicsLoop() {
  int level = 2;
  int waterDepth = getWaterDepth();
  if (waterDepth >= level - 1) {
    digitalWrite(waterPump, LOW);
    digitalWrite(nutrientPump, LOW);
  } else {
    digitalWrite(waterPump, HIGH);
    digitalWrite(nutrientPump, HIGH);
  }
}

// Controls humidity of Farm. Author: Anya Li. Editted by: Stone Mao
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

//INSTANCE METHODS
float getMainTemp() { // For main temperature sensorz
  int readData = DHT.read22(dataPin);
  int faren = (DHT.temperature * 9/5 + 28.5);
  Serial.print("Temp: "); Serial.println(faren);
  return faren;
}

float getTemp2() {
  return 67;
}

float getBoxHumidity() {
  Serial.print("Humidity: ");Serial.println(DHT.humidity);
  return DHT.humidity;
}

float getWaterDepth() {
  int val = analogRead(waterDepthSensor);
  return abs((val * 4.0) / 600);
}
