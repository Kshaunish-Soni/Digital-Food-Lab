#include <Scheduler.h>

#include <Time.h>
#include <TimeLib.h>


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


//Different Pin #'s
const int growthLight = 2;

void setup() {
  Serial.begin(9600);
  setTime(0,0,0,sDay,sMonth,sYear);

  // Light Setup
  pinMode(growthLight, OUTPUT);

  //Different Loop Schedules
  Scheduler.startLoop(lightCycle);
  Scheduler.startLoop(timeLoop);
}

void loop() {
  

}

//LIGHT FUNCTIONS
void lightCycle(){
  digitalWrite(growthLight, HIGH);
  delay(5.76E7);    // 16 hours of light
  digitalWrite(growthLight, LOW);
  delay(7.2E6);     // 2 hours of dark 
}

//Saving time to raspberry pi / computer
void timeLoop(){
  curDay = day();
  curMonth = month();
  curHr = hour();
  curMin = minute();
  curSec = second();
  delay(30000); //30sec dela
}

