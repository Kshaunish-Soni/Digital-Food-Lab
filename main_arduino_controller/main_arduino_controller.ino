#include <Time.h>
#include <TimeLib.h>
#include <Wire.h>
//Comment out #include <util/delay>
#include <cactus_io_AM2315.h> //Download zip from: http://cactus.io/hookups/sensors/temperature-humidity/am2315/hookup-arduino-to-am2315-temp-humidity-sensor
#include <Scheduler.h>

//data array
float data[] = {getMainTemp(), getTemp2(),getBoxHumidity(), getWaterDepth()};

//Start Time -- needed for the light system and harvesting
int sDay = 1;
int sMonth = 1;
int sYear = 17;

//Current Time -- Will update every 30 sec
int curDay = sDay;
int curMonth = sMonth;
int curHr = 0;
int curMin = 0;
int curSec = 0;

//Target Time -- How much time has elapsed in light cycle
int timeElapsed = 0;

//Is it day or night
boolean isDay = true;

//Light Pin #'s
const int growthLight = 0;

//Temperature Control Pin #'s
const int tempPin = 0;   // 0 = digital pin number temp sensor is hooked up to
const int coolerPin = 1;    // 1# = digital pin number cooler is hooked up to
const int ceramicHeater = 2; // 2# = digital pin number heater is hooked up to
float targetTemp = 65; // 65 deg F morning 55 deg F night

// Humidity Control
const int humidifier = 0; // digital pin humidifer is hooked up to
AM2315 am2315;

//Hydroponics & Pump Digital Pins
const int waterDepthSensor = 0;
const int waterPump = 0;
const int nutrientPump = 0;

void setup() {
  Serial.begin(9600);
  setTime(0, 0, 0, sDay, sMonth, sYear);

  // Light Setup
  pinMode(growthLight, OUTPUT);

  // Temperature Control Setup
  pinMode(tempPin, INPUT);
  pinMode(coolerPin, OUTPUT);
  pinMode(ceramicHeater, OUTPUT);

  // Humidifier Setup
  pinMode(humidifier, OUTPUT);
  digitalWrite(humidifier, LOW); // default, humidifier is off
  // Initialize the Adafruit Humidity and Temp Sensor
  if (!am2315.begin()) {
    Serial.println("am2315 not found. Wiring? Connection?");
    while (1);
  }

  // Water and Nutrient Pump
  pinMode(waterDepthSensor, INPUT);
  pinMode(waterPump, OUTPUT);
  pinMode(nutrientPump, OUTPUT);
  
  // Allows us to run different loops simultaneously -- COMMENT OUT ONES YOU AREN'T GONNA TEST!
  Scheduler.startLoop(lightCycle);
  Scheduler.startLoop(timeLoop);
  Scheduler.startLoop(tempControlLoop);
  Scheduler.startLoop(humidityCheck);
  Scheduler.startLoop(hydroponicsLoop);
}

// Main Debug Loop
void loop() {
  Serial.print("Virtual Time: "); Serial.print(hour());Serial.print(":");Serial.print(minute());Serial.print("\t");Serial.print(month());Serial.print("/");Serial.println(day());
  Serial.print("Main Temperature (C): ");  Serial.println(getMainTemp());
  Serial.print("am2315 Dual Sensor, Humidity: "); Serial.println(am2315.getHumidity());
  Serial.print("am2315 Dual Sensor, Temperature in C: "); Serial.println(am2315.getTemperature_C());
  Serial.print(data);
  delay(5000);
}

// LIGHT FUNCTIONS. Author: Anya Li. Editted By: Stone
void lightCycle() {
  digitalWrite(growthLight, HIGH);
  isDay = true;
  targetTemp = 65;
  delay(5.76E7);    // 16 hours of light
  digitalWrite(growthLight, LOW);
  targetTemp = 55;
  isDay = false;
  delay(7.2E6);     // 2 hours of dark
}

//Saving time to raspberry pi / computer
void timeLoop() {
  curDay = day();
  curMonth = month();
  curHr = hour();
  curMin = minute();
  curSec = second();
  delay(30000); //30sec delay
}

// Controls the temperature. Author: Anya Li; Editted By: Stone
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

// Controls humidity of Farm. Author: Anya Li. Editted by: Stone Mao
void humidityCheck() {
  int humidityValue = am2315.getHumidity();
  if (humidityValue < 65.00){
    digitalWrite(humidifier, HIGH);  // turn humidifier on if humidity is below 65%
  }
  
  else if (humidityValue >= 67.00)
  {
    digitalWrite(humidifier, LOW);  // turn humidifier off if humidity is greater or equal to 67%
  }
  
  delay(30000);   // check every 30 seconds
}

void hydroponicsLoop() {
  int level = 2;
  int waterDepth = getWaterDepth();
  if(waterDepth>level-0){
    digitalWrite(waterPump, LOW);
    digitalWrite(nutrientPump, LOW);
  } else {
    digitalWrite(waterPump, HIGH);
    digitalWrite(nutrientPump, HIGH);
  }
  delay(2000);
}

//Instance Methods -- For convenience
float getMainTemp() { // For main temperature sensor
  int v = 5.0; // Voltage which arduino provides
  int reading = analogRead(tempPin);
  float voltage = reading * v / 1024.0;
  return (voltage - 0.5) * 100;
}

float getTemp2(){
  return am2315.getTemperature_C();
}

float getBoxHumidity(){
  return am2315.getHumidity();
}

float getWaterDepth(){
  return analogRead(waterDepthSensor);
}

