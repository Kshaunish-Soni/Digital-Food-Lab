#include <SD.h>
#include <RTClib.h>
#include <DHT.h>
int dht_dpin = 1;
int pHPin=A2;
int pHPlusPin = 2;
int pHMinPin = 3;
int ventilatorPin = 4;
int floatLowPin = 8;
int floatHighPin = 7;
int growLights = 5;
const int chipSelect = 53;

int x,y;
int page = 0;
int tankProgState = 1;
float pH;
boolean smoothPh = 0;
float Offset = 0.00;
unsigned long int avgValue;
float b;
int buf[14], temp;

const int numReadings = 10;
int readings[numReadings];
int index = 0;
int total = 0;
int average = 0;

int count = 0;

int ledState = LOW;       // variables for pulsing the pump
long previousMillis = 0;
long pinHighTime = 100;
long pinLowTime = 7500;
long pinTime = 100;

int sdState = LOW;
long sdPreviousMillis = 0;
long sdTime = 7500;

int pmem =0;
float SetPoint;
float HysterisMin;
float HysterisPlus;                //Maximum deviation from Setpoint
float SetHysteris;                 //Holds the value for Hysteris
float FanTemp;                     //Holds the set value for temperature
float FanHumid;                    //Holds the set value for humidity
float fanHysteris = 2;             //Set value for hysteris tuning Fan
float LightTime;                   //Holds the set value for amount of time plants should have light

int lightADCReading;               //variables for measuring the light
double currentLightInLux;          //              |
double lightInputVoltage;          //              |
double lightResistance;            //              |

float LightOn;                      //Time the plants have had light
float proportion_to_light = LightTime / 24;    //calculate desired hours of light total and supplemental daily based on above values
float seconds_light = 0;
float proportion_lit;
float start_time;
float seconds_elapsed;
float seconds_elapsed_total;
float seconds_for_this_cycle;

DateTime now;

#define DHTTYPE DHT22 
byte bGlobalErr;
byte dht_dat [4];


void setup() {
  // put your setup code here, to run once:
  smoothArraySetup();
  logicSetup();
  timeSetup();
  SDSetup();
  start_time = now.get();
  seconds_elapsed_total = 0;
  
}

void loop() {
  // put your main code here, to run repeatedly:
  logicLoop();
  FanControl();
  TankProgControl();
  LightControl();
  SDLoop();
}


