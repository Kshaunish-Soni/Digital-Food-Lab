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

const int waterIn = 0;
const int phUp = 1;
const int phDown = 2;
const int nutrient = 9;
const int waterOut = 7;

long prevNutrientMillis = 0;
boolean onceToday = false;
boolean onceToday1 = false;

////PH SETUP
//#define SensorPin A0            //pH meter Analog output to Arduino Analog Input 0
//#define Offset 0.00            //deviation compensate
//
//#define samplingInterval 20
//#define printInterval 800
//#define ArrayLenth  40    //times of collection
//int pHArray[ArrayLenth];   //Store the average value of the sensor feedback
//int pHArrayIndex=0;  
//int timesChanged = 0;

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
  pinMode(waterOut, OUTPUT);
  pinMode(nutrient, OUTPUT);
  pinMode(analogInPin, INPUT);
  pinMode(waterOut, OUTPUT);
  pinMode(phUp, OUTPUT);
  pinMode(phDown, OUTPUT);}

void loop() {

  cerealloop();
  tempControlLoop();
  lightControlLoop();
//  hydroponicsLoop();
  humidityCheck();
  nutrientLoop();
//  phLoop();
  
//HYDROPONICS LOOP
  float value = analogRead(A1);

  if(value < 100){
    digitalWrite(waterOut, HIGH);
  } 
  else {
       digitalWrite(waterOut, LOW);
  }
  
  //PRINT STUFF
  Serial.print(getMainTemp());
    Serial.print("\t");
  Serial.print(getTemp2());
    Serial.print("\t");
  Serial.print(getBoxHumidity());
    Serial.print("\t");
  Serial.print(value);
  Serial.print("\t");
  Serial.println(dayElapsed);
  //Serial.print(hours());

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
    if (currentMillis - prevNutrientMillis >= 13700) { // If the difference is more than 12 sec
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
  return sensorValue;
}

//void phLoop() {
//  static unsigned long samplingTime = millis();
//  static unsigned long printTime = millis();
//  static float pHValue,voltage;
//  if(millis()-samplingTime > samplingInterval)
//  {
//      pHArray[pHArrayIndex++]=analogRead(SensorPin);
//      if(pHArrayIndex==ArrayLenth)pHArrayIndex=0;
//      voltage = avergearray(pHArray, ArrayLenth)*5.0/1024;
//      pHValue = 3.5*voltage+Offset;
//      samplingTime=millis();
//  }
//  if(millis() - printTime > printInterval)   //Every 800 milliseconds, print a numerical, convert the state of the LED indicator
//  {
//  Serial.print("Voltage:");
//        Serial.print(voltage,2);
//        Serial.print("    pH value: ");
//  Serial.println(pHValue,2);
//        printTime=millis();
//  }
//
////  if (pHValue > 6.5) {
////    digitalWrite(, HIGH);
////    
////  }
////  else  if {pHValue < 5) {
////    digitalWrite(, HIGH);   
////  }
//}
//
//double avergearray(int* arr, int number){
//  int i;
//  int max,min;
//  double avg;
//  long amount=0;
//  if(number<=0){
//    Serial.println("Error number for the array to avraging!/n");
//    return 0;
//  }
//  if(number<5){   //less than 5, calculated directly statistics
//    for(i=0;i<number;i++){
//      amount+=arr[i];
//    }
//    avg = amount/number;
//    return avg;
//  }else{
//    if(arr[0]<arr[1]){
//      min = arr[0];max=arr[1];
//    }
//    else{
//      min=arr[1];max=arr[0];
//    }
//    for(i=2;i<number;i++){
//      if(arr[i]<min){
//        amount+=min;        //arr<min
//        min=arr[i];
//      }else {
//        if(arr[i]>max){
//          amount+=max;    //arr>max
//          max=arr[i];
//        }else{
//          amount+=arr[i]; //min<=arr<=max
//        }
//      }//if
//    }//for
//    avg = (double)amount/(number-2);
//  }//if
//  return avg;  
//}

