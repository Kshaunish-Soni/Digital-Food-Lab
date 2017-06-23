#include <Time.h>
#include <TimeLib.h>
#include <Wire.h>
//Comment out #include <util/delay>
#include <cactus_io_AM2315.h> //Download zip from: http://cactus.io/hookups/sensors/temperature-humidity/am2315/hookup-arduino-to-am2315-temp-humidity-sensor
#include <Scheduler.h>


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

//Humidity and Temp Sensor Instance

void setup() {
  Serial.begin(9600);
  setTime(0, 0, 0, sDay, sMonth, sYear);

  // Light Setup
  pinMode(growthLight, OUTPUT);

  // Temperature Control Setup
  pinMode(tempPin, INPUT);
  pinMode(coolerPin, OUTPUT);
  pinMode(ceramicHeater, OUTPUT);

  //Allows us to run different loops simultaneously -- COMMENT OUT ONES YOU AREN'T GONNA TEST!
  Scheduler.startLoop(lightCycle);
  Scheduler.startLoop(timeLoop);
  Scheduler.startLoop(tempControlLoop);
}

void loop() {


}

//LIGHT FUNCTIONS. Author: Anya Li
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

// Controls the temperature. Author: Anya Li; Edit: Stone
void tempControlLoop() {
  int tempValue = getTemp();
  Serial.print("tempValue: ");
  Serial.println(tempValue);

  //Cooler and Heater are Digital (On or Off)
  if (tempValue >= targetTemp - 5 && tempValue <= targetTemp + 5) {
    digitalWrite(coolerPin, LOW);    // default, cooler should be off
    digitalWrite(ceramicHeater, LOW);  // default heater should be off
  } else { //Will heat up to the targetTemp regardless of 5 deg threshold
    if (tempValue < targetTemp) // min temp
    {
      pinMode(ceramicHeater, HIGH);   // turn on heater
    }
    else if (tempValue > targetTemp) // max temp
    {
      pinMode(coolerPin, HIGH);   // turn on cooler
    }
  }
}

//Instance Methods -- For convenience
float getTemp() {
  int v = 5.0; // Voltage which arduino provides
  int reading = analogRead(tempPin);
  float voltage = reading * v / 1024.0;
  return (voltage - 0.5) * 100;
}

