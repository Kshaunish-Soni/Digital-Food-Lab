int motorPin = 10;     //where the bushing motor will go. Change this for any other pin if need be.
#include <Stepper.h>
int previous = 0;
const int STEPS = 200; //change this to fit the numbers
const int Location1x = 2.5*5;   // variables for the x and y locations of the plants. Change this to fit the locations.
const int Location2x = 6.5*5;
const int Location3x = 10.5*5;
const int Location4x = 14.5*5;
const int Location5x = 18.5*5;
const int Location1y = 2.5*5;
const int Location2y = 6.5*5;
const int Location3y = 10.5*5;
const int Location4y = 14.5*5;
Stepper myStepperx(STEPS, 2, 3);
Stepper mySteppery(STEPS, 4, 5);
Stepper myStepperz(STEPS, 6, 7);
Stepper mySteppergrab(STEPS, 8, 9);



void setup() {
  pinMode(sensorPin, INPUT);      //acknowledging that the sensor is in input
  myStepperx.setSpeed(120);       // setting the speed (rpm) of 4 stepper motors
  mySteppery.setSpeed(120);
  myStepperz.setSpeed(120);
  mySteppergrab.setSpeed(60);
  pinMode(motorPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("clockwise");
    myStepperx.step(Location1x*STEPS);
    delay(100);
    mySteppery.step(Location2x*STEPS);
    delay(100);
    mySteppergrab.step(0.1*STEPS);    // 18 degrees, basically enought to open the claw to a 150~ angle.
    myStepperz.step(15*STEPS);
    delay(200);     
    mySteppergrab.step(-0.1*STEPS);
   
    Serial.println("counterclockwise");
    myStepperz.step(-15*STEPS);     // moves the chassis back to (0,0) the original position
    delay(100);
    myStepperx.step(-Location1x*STEPS);
    delay(100);
    mySteppery.step(-Location2y*STEPS);
    delay(100);
    mySteppergrab.step(0.1*STEPS);          // Open and close the claw.
    mySteppergrab.step(-0.1*STEPS);
    delay(10000);

}

}
