#include <Time.h>
#include <TimeLib.h>
#include <Wire.h>
//Comment out #include <util/delay>
#include <cactus_io_AM2315.h> //Download zip from: http://cactus.io/hookups/sensors/temperature-humidity/am2315/hookup-arduino-to-am2315-temp-humidity-sensor
#include <Scheduler.h>

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
const int tempPin = 0;   // 0 = digital pin number temp sensor is hooked up to
const int coolerPin = 4;    // 1# = digital pin number cooler is hooked up to
const int ceramicHeater = 5; // 2# = digital pin number heater is hooked up to
float targetTemp = 65; // 65 deg F morning 55 deg F night

// Humidity Control
const int humidifier = 6; // digital pin humidifer is hooked up to
AM2315 am2315;

//Hydroponics & Pump Digital Pins
const int waterDepthSensor = 0;
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
  if (Serial.available() > 0) {
    int read1 = Serial.read();
    int read2 = Serial.read();
    int timeArray[4];
    float myData = read1 * 10000;
    for (int i = 0; i < 4; i++) {
      timeArray[3 - i] = ((int)myData) % 100;
      myData /= 100;
    }
    dayElapsed = read2;
    setTime(timeArray[2], timeArray[3], 0, timeArray[1], timeArray[0], sYear);
  }

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
  if (Serial.available() > 0) {
    Serial.write(getMainTemp());
    Serial.write(getTemp2());
    Serial.write(getBoxHumidity());
    Serial.write(getWaterDepth());
    Serial.write(dayElapsed);
  }
  delay(15000);
}

// LIGHT FUNCTIONS. Author: Anya Li. Editted By: Stone
void lightCycle() {
  /*
   * After seed germinates (around 6 days), lights will turn on and follow cycle
   * WILL ADD SALENIS DATA ON
  */
  if (dayElapsed > 6) {
    digitalWrite(growthLight, HIGH);
    isDay = true;
    targetTemp = 65;
    delay(5.76E7);    // 16 hours of light
    digitalWrite(growthLight, LOW);
    targetTemp = 55;
    isDay = false;
    delay(7.2E6);     // 2 hours of dark
  } else {
    digitalWrite(growthLight, LOW);
  }
}

//Saving time to raspberry pi / computer
void timeLoop() {
  delay(8.64e+7); // 24 Hrs
  dayElapsed++;
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

//Serial Connection handshake
void establishContact() {
  while (Serial.available() <= 0) { // If not established
    Serial.print("A"); // Will send A
    delay(300);
  }
}

//Instance Methods -- For convenience
float getMainTemp() { // For main temperature sensor
  int v = 5.0; // Voltage which arduino provides
  int reading = analogRead(tempPin);
  float voltage = reading * v / 1024.0;
  return (voltage - 0.5) * 100;
}

float getTemp2() {
  return am2315.getTemperature_C();
}

float getBoxHumidity() {
  return am2315.getHumidity();
}

float getWaterDepth() {
  return analogRead(waterDepthSensor);
}

