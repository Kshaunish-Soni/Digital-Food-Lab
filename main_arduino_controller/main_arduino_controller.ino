#include <Time.h>
#include <TimeLib.h>


//Start Time -- needed for the light system and harvesting


void setup() {
  Serial.begin(9600);
  setTime(12,0,0,1,1,11);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(year());
  delay(3000);
}

