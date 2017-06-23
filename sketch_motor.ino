int sensorPin = 13;
int motorPin = 2;
#include <Stepper.h>
int previous = 0;
int timerdelay;
const int STEPS = 200; //change this to fit the numbers
const int Location1x = 2.5*5;   // variables for the x and y locations of the plants.
const int Location2x = 6.5*5;
const int Location3x = 10.5*5;
const int Location4x = 14.5*5;
const int Location5x = 18.5*5;
const int Location1y = 2.5*5;
const int Location2y = 6.5*5;
const int Location3y = 10.5*5;
const int Location4y = 14.5*5;
Stepper myStepperx(STEPS, 8, 9);
Stepper mySteppery(STEPS, 10, 11);
Stepper myStepperz(STEPS, 6, 7);
Stepper mySteppergrab(STEPS, 12, 13);
int moveTo0();        // names of all the functions 
int moveTo1();
int moveTo2();
int moveTo3();
int moveTo4();
int moveTo5();
int moveTo6();

void setup() {
  pinMode(sensorPin, INPUT);      //acknowledging that the sensor is in input
  myStepperx.setSpeed(200);       // setting the speed (rpm) of 4 stepper motors
  mySteppery.setSpeed(200);
  myStepperz.setSpeed(100);
  mySteppergrab.setSpeed(60);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int val = analogRead(0);        // finding the value of imaging sensors, which are displayed with a number, dictating a specific location (x,y,z coords)
  if (sensorPin, val=0)           // if then elseif loop. TLDR if the imaging sensor gives a certain value for a location, the stepper motors
  {                               // will go to that certain location, which is dictated in a function.
    moveTo0();
  } 
  else if(sensorPin, val=1)
  {
   moveTo1();
  }
  else if(sensorPin, val=2)
  {
    moveTo2();
  }
  else if(sensorPin, val=3)
  {
    moveTo3();
  }
  else if(sensorPin, val=4)
  {
    moveTo4();
  }
  else if(sensorPin, val=5)
  {
    moveTo5();
  }
  else if(sensorPin, val=6)
  {
    moveTo6();
  }
  else if(sensorPin, val=7)
  {
    moveTo7();
  }
  else if(sensorPin, val=8)
  {
    moveTo8();
  }
  else if(sensorPin, val=9)
  {
    moveTo9();
  }
  else if(sensorPin, val=10)
  {
    moveTo10();
  }

void moveTo0(); {
  Serial.println("clockwise");
    myStepperx.step(Location1x*STEPS);
    mySteppery.step(Location2x*STEPS);
    delay(100);
    mySteppergrab.step(0.1*STEPS);    // 18 degrees, basically enought to open the claw to a 150~ angle.
    myStepperz.step(15*STEPS);
    delay(200);
    digitalWrite(motorPin, HIGH);     // turn on the razor blade motor.
    mySteppergrab.step(-0.1*STEPS);
    digitalWrite(motorPin, LOW);      // turn off the razor blade motor.
    
    Serial.println("counterclockwise");
    myStepperz.step(previous-15*STEPS);     // moves the chassis back to (0,0) the original position
    delay(100);
    myStepperx.step(previous-Location1x*STEPS);
    mySteppery.step(previous-Location2y*STEPS);
    mySteppergrab.step(0.1*STEPS);          // Open and close the claw.
    mySteppergrab.step(-0.1*STEPS);
    delay(10000);

    
}

void moveTo1(); {
  Serial.println("clockwise");
    myStepperx.step(Location1x*STEPS);
    mySteppery.step(Location4y*STEPS);
    delay(100);
    mySteppergrab.step(0.1*STEPS);
    myStepperz.step(15*STEPS);
    delay(200);]
    digitalWrite(motorPin, HIGH);
    mySteppergrab.step(-0.1*STEPS);
    digitalWrite(motorPin, LOW);

    Serial.println("counterclockwise");
    myStepperz.step(previous-15*STEPS);
    delay(100);
    myStepperx.step(previous-Location1x*STEPS);
    mySteppery.step(previous-Location4y*STEPS);
    mySteppergrab.step(0.1*STEPS);
    mySteppergrab.step(-0.1*STEPS);
    delay(10000);
}

void moveTo2(); {
  Serial.println("clockwise");
    myStepperx.step(Location2x*STEPS);
    mySteppery.step(Location1y*STEPS);
    myStepperz.step(15*STEPS);
    mySteppergrab.step(0.1*STEPS); 
    delay(200);
    digitalWrite(motorPin, HIGH);
    mySteppergrab.step(-0.1*STEPS);
    digitalWrite(motorPin, LOW);

    Serial.println("counterclockwise");
    myStepperz.step(previous-15*STEPS);
    myStepperx.step(previous-Location2x*STEPS);
    mySteppery.step(previous-Location1y*STEPS);
    mySteppergrab.step(0.1*STEPS);
    mySteppergrab.step(-0.1*STEPS);
    delay(10000);
}

void moveTo3(); {
  Serial.println("clockwise");
    myStepperx.step(Location2x*STEPS);
    mySteppery.step(Location3y*STEPS);
    myStepperz.step(15*STEPS);
    mySteppergrab.step(0.1*STEPS);
    delay(200);
    digitalWrite(motorPin, HIGH);
    mySteppergrab.step(-0.25*STEPS);
    digitalWrite(motorPin, LOW);

    Serial.println("counterclockwise");
    myStepperz.step(previous-15*STEPS);
    myStepperx.step(previous-Location2x*STEPS);
    mySteppery.step(previous-Location3y*STEPS);
    mySteppergrab.step(0.1*STEPS);
    mySteppergrab.step(-0.1*STEPS);
    delay(10000);
}
 
void moveTo4(); {
  Serial.println("clockwise");
    myStepperx.step(Location3x*STEPS);
    mySteppery.step(Location2y*STEPS);
    myStepperz.step(15*STEPS);
    mySteppergrab.step(0.1*STEPS);
    delay(200);
    digitalWrite(motorPin, HIGH);
    mySteppergrab.step(-0.1*STEPS);
    digitalWrite(motorPin, LOW);

    Serial.println("counterclockwise");
    myStepperz.step(previous-15*STEPS);
    myStepperx.step(previous-Location3x*STEPS);
    mySteppery.step(previous-Location2y*STEPS);
    mySteppergrab.step(0.1*STEPS);
    mySteppergrab.step(-0.1*STEPS);
    delay(10000);
}

void moveTo5(); {
  Serial.println("clockwise");
    myStepperx.step(Location3x*STEPS);
    mySteppery.step(Location4y*STEPS);
    myStepperz.step(15*STEPS);
    mySteppergrab.step(0.1*STEPS);
    delay(200);
    digitalWrite(motorPin, HIGH);
    mySteppergrab.step(-0.1*STEPS);
    digitalWrite(motorPin, LOW);
    
    Serial.println("counterclockwise");
    myStepperz.step(previous-15*STEPS);
    myStepperx.step(previous-Location3x*STEPS);
    mySteppery.step(previous-Location4y*STEPS);
    mySteppergrab.step(0.1*STEPS);
    mySteppergrab.step(-0.1*STEPS);
    delay(10000);
}

void moveTo6(); {
  Serial.println("clockwise");
    myStepperx.step(Location4x*STEPS);
    mySteppery.step(Location1y*STEPS);
    myStepperz.step(15*STEPS);
    mySteppergrab.step(0.1*STEPS);
    delay(200);
    digitalWrite(motorPin, HIGH);
    mySteppergrab.step(-0.1*STEPS);
    digitalWrite(motorPin, LOW);

    Serial.println("counterclockwise");
    myStepperx.step(previous-Location4x*STEPS);
    mySteppery.step(previous-Location1y*STEPS);
    myStepperz.step(previous-15*STEPS);
    mySteppergrab.step(0.1*STEPS);
    mySteppergrab.step(-0.1*STEPS);
    delay(10000);
}

  void moveTo7(); {
    Serial.println("clockwise");
    myStepperx.step(Location4x*STEPS);
    mySteppery.step(Location3y*STEPS);
    myStepperz.step(15*STEPS);
    mySteppergrab.step(0.1*STEPS);
    delay(200);
    digitalWrite(motorPin, HIGH);
    mySteppergrab.step(-0.1*STEPS);
    digitalWrite(motorPin, LOW);

    Serial.println("counterclockwise");
    myStepperx.step(previous-Location4x*STEPS);
    mySteppery.step(previous-Location3y*STEPS);
    myStepperz.step(previous-15*STEPS);
    mySteppergrab.step(0.1*STEPS);
    mySteppergrab.step(-0.1*STEPS);
    delay(10000);
}

  void moveTo8();{
    Serial.println("clockwise");
    myStepperx.step(Location5x*STEPS);
    mySteppery.step(Location2y*STEPS);
    myStepperz.step(15*STEPS);
    mySteppergrab.step(0.1*STEPS);
    delay(200);
    digitalWrite(motorPin, HIGH);
    mySteppergrab.step(-0.1*STEPS);
    digitalWrite(motorPin, LOW);

    Serial.println("counterclockwise");
    myStepperx.step(previous-Location5x*STEPS);
    mySteppery.step(previous-Location2y*STEPS);
    myStepperz.step(previous-15*STEPS);
    mySteppergrab.step(0.1*STEPS);
    mySteppergrab.step(-0.1*STEPS);
    delay(10000);
  }
  void MoveTo9(); {
    Serial.println("clockwise");
    myStepperx.step(Location5x*STEPS);
    mySteppery.step(Location4y*STEPS);
    myStepperz.step(15*STEPS);
    mySteppergrab.step(0.1*STEPS);
    delay(200);
    digitalWrite(motorPin, HIGH);
    mySteppergrab.step(-0.1*STEPS);
    digitalWrite(motorPin, LOW);

    Serial.println("counterclockwise");
    myStepperx.step(previous-Location5x*STEPS);
    mySteppery.step(previous-Location4y*STEPS);
    myStepperz.step(previous-15*STEPS);
    mySteppergrab.step(0.1*STEPS);
    mySteppergrab.step(-0.1*STEPS);
    delay(10000);
