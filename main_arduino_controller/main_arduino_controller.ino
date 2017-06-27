
#define dataPin A3 // Analog Pin sensor is connected to

#include <Time.h>
#include <TimeLib.h>
#include <Wire.h>
#include <Scheduler.h>

boolean once = false;
//Start Time -- needed for the light system and harvesting
int dayElapsed = 0;
int sYear = 2017;

//Target Time -- How much time has elapsed in light cycle
int timeElapsed = 0;

//Is it day or night
boolean isDay = true;

//Light Pin #'s
const int growthLight = 3;

//Temperature Control Pin #'s
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
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  //Establish contact with Raspberry Pi
  establishContact();
  //Get time from Raspberry pi


  // Light Setup
  pinMode(growthLight, OUTPUT);

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

  // Allows us to run different loops simultaneously -- COMMENT OUT ONES YOU AREN'T GONNA TEST!
  Scheduler.startLoop(lightCycle);
  Scheduler.startLoop(tempControlLoop);
  Scheduler.startLoop(humidityCheck);
  Scheduler.startLoop(hydroponicsLoop);
  Scheduler.startLoop(nutrientLoop);
}

// Main Debug Loop
void loop() {
  Serial.flush();
  if (Serial.available() > 0) {
    if (!once) {
      int read1 = Serial.parseInt();
      Serial.flush();
      int read2 = Serial.parseInt();
      Serial.print("Date time: "); Serial.println(read1);
      Serial.print("Day Elapsed: "); Serial.println(read2);
      int timeArray[4];
      float myData = read1;
      for (int i = 0; i < 4; i++) {
        timeArray[3 - i] = ((int)myData) % 100;
        myData /= 100;
      }
      dayElapsed = read2;
      setTime(timeArray[2], timeArray[3], 0, timeArray[1], timeArray[0], sYear);
      once = true;
    }

    Serial.print(getMainTemp());
    Serial.print(getTemp2());
    Serial.print(getBoxHumidity());
    Serial.print(getWaterDepth());
    Serial.print(dayElapsed);
    dayElapsed = Serial.parseInt();
  }
  Serial.flush();
  delay(1000);
}

// LIGHT FUNCTIONS. Author: Anya Li. Editted By: Stone
void lightCycle() {
  /*
     After seed germinates (around 6 days), lights will turn on and follow cycle
     WILL ADD SALENIS DATA ON
  */
  Serial.print("Day: "); Serial.println(dayElapsed);
  if (dayElapsed > 3) {
    digitalWrite(growthLight, HIGH);
    //Serial.println("Grow Light ON!");
    isDay = true;
    targetTemp = 65;
    delay(7.2e7);    // 16 hours of light
    digitalWrite(growthLight, LOW);
    targetTemp = 55;
    isDay = false;
    delay(1.44E7);     // 2 hours of dark
  } else {
    digitalWrite(growthLight, LOW);
    delay(2000);
  }
}

//Saving time to raspberry pi / computer
void timeLoop() {
  delay(8.64e+7); // 24 Hrs
  dayElapsed++;
}

// Controls the temperature. Author: Anya Li; Editted By: Stone
void tempControlLoop() {
  //Serial.println("Hello from tempControl");
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
  delay(3000);
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

  delay(30000);   // check every 30 seconds
}

void hydroponicsLoop() {
  int level = 2;
  int waterDepth = getWaterDepth();
  if (waterDepth > level - 0) {
    digitalWrite(waterPump, LOW);
    digitalWrite(nutrientPump, LOW);
  } else {
    digitalWrite(waterPump, HIGH);
    digitalWrite(nutrientPump, HIGH);
  }
  delay(2000);
}

void nutrientLoop() {
  // put your main code here, to run repeatedly:
  digitalWrite(nutrients, HIGH);
  delay(12000); // pump nutrients for 12 seconds
  digitalWrite(nutrients, LOW);
  delay(5.184E8); // pump nutrients every 6 days
}

//Serial Connection handshake
void establishContact() {
  while (Serial.available() <= 0) { // If not established
    Serial.print("A"); // Will send A
    delay(200);
  }
}

//Instance Methods -- For convenience
float getMainTemp() { // For main temperature sensorz
  return targetTemp;
}

float getTemp2() {
  return 67;
}

float getBoxHumidity() {
  return 65;
}

float getWaterDepth() {
  int val = analogRead(waterDepthSensor);
  return abs((val * 4.0) / 600);
}
