int sensorPin = 13;
int motorPin = 2;     //where the bushing motor will go. Change this for any other pin if need be.
#include <Stepper.h>
const int STEPS = 200; //change this to fit the numbers
const int Location1x = 2.5*5*STEPS;   // variables for the x, y, and z locations of the plants. Change this to fit the locations.
const int Location2x = 6.5*5*STEPS;
const int Location3x = 10.5*5*STEPS;
const int Location4x = 14.5*5*STEPS;
const int Location5x = 18.5*5*STEPS;
const int Location1y = 2.5*5*STEPS;
const int Location2y = 6.5*5*STEPS;
const int Location3y = 10.5*5*STEPS;
const int Location4y = 14.5*5*STEPS;
const int Locationz = 15*STEPS;
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
int moveTo7();
int moveTo8();
int moveTo9();
int moveTo10();
int moveTo11();
int moveTo12();
int moveTo13();
int moveTo14();
int moveT015();
int moveTo16();
int moveTo17();
int moveTo18();
int moveTo19();


void setup() {
  pinMode(sensorPin, INPUT);      //acknowledging that the sensor is in input
  myStepperx.setSpeed(120);       // setting the speed (rpm) of 4 stepper motors
  mySteppery.setSpeed(120);
  myStepperz.setSpeed(120);
  mySteppergrab.setSpeed(120);
  pinMode(motorPin, OUTPU);       // acknowledging that the motor is the output
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
  else if(sensorPin, val=11)
  {
    moveTo11();
  }
  else if(sensorPin, val=12)
  {
    moveTo12();
  }
  else if(sensorPin, val=13)
  {
    moveTo13();
  }
  else if(sensorPin, val=14)
  {
    moveTo14();
  }
  else if(sensorPin, val=15)
  {
    moveTo15();
  }
  else if(sensorPin, val=16)
  {
    moveTo16();
  }
  else if(sensorPin, val=17)
  {
    moveTo17();
  }
  elese if(sensorPin, val=18)
  {
    moveTo18();
  }
  else if(sensorPin, val=19)
  {
    moveTo19();
  }

void moveTo0(); {
  Serial.println("clockwise");
    myStepperx.step(Location1x);
    mySteppery.step(Location1y);
    delay(100);
    mySteppergrab.step(0.1*STEPS);    // 18 degrees, basically enought to open the claw to a 150~ angle.
    myStepperz.step(Locationz);
    delay(200);
    digitalWrite(motorPin, HIGH);     // turn on the razor blade motor.
    mySteppergrab.step(-0.1*STEPS);
    digitalWrite(motorPin, LOW);      // turn off the razor blade motor.
    
    Serial.println("counterclockwise");
    myStepperz.step(-Locationz);     // moves the chassis back to (0,0) the original position
    delay(100);
    myStepperx.step(-Location1x);
    mySteppery.step(-Location1y);
    mySteppergrab.step(0.1*STEPS);          // Open and close the claw.
    mySteppergrab.step(-0.1*STEPS);
    delay(10000);

    
}

void moveTo1(); {                         // same thing done 10 times, one function for each location.
  Serial.println("clockwise");            // Location variables are interchangeable depending on the location
    myStepperx.step(Location1x);    // of the plant. Calibration may be needed based on design.
    mySteppery.step(Location2y);
    delay(100);
    mySteppergrab.step(0.1*STEPS);
    myStepperz.step(Locationz);
    delay(200);]
    digitalWrite(motorPin, HIGH);
    mySteppergrab.step(-0.1*STEPS);
    digitalWrite(motorPin, LOW);

    Serial.println("counterclockwise");
    myStepperz.step(-Locationz);
    delay(100);
    myStepperx.step(-Location1x);
    mySteppery.step(-Location2y);
    mySteppergrab.step(0.1*STEPS);
    mySteppergrab.step(-0.1*STEPS);
    delay(10000);
}

void moveTo2(); {
  Serial.println("clockwise");
    myStepperx.step(Location1x);
    mySteppery.step(Location3y);
    myStepperz.step(Locationz);
    mySteppergrab.step(0.1*STEPS); 
    delay(200);
    digitalWrite(motorPin, HIGH);
    mySteppergrab.step(-0.1*STEPS);
    digitalWrite(motorPin, LOW);

    Serial.println("counterclockwise");
    myStepperz.step(-Locationz);
    myStepperx.step(-Location1x);
    mySteppery.step(-Location3y);
    mySteppergrab.step(0.1*STEPS);
    mySteppergrab.step(-0.1*STEPS);
    delay(10000);
}

void moveTo3(); {
  Serial.println("clockwise");
    myStepperx.step(Location1x);
    mySteppery.step(Location4y);
    myStepperz.step(Locationz);
    mySteppergrab.step(0.1*STEPS);
    delay(200);
    digitalWrite(motorPin, HIGH);
    mySteppergrab.step(-0.25*STEPS);
    delay(200);
    digitalWrite(motorPin, LOW);

    Serial.println("counterclockwise");
    myStepperz.step(-Locationz);
    myStepperx.step(-Location1x);
    mySteppery.step(-Location4y);
    mySteppergrab.step(0.1*STEPS);
    mySteppergrab.step(-0.1*STEPS);
    delay(10000);
}
 
void moveTo4(); {
  Serial.println("clockwise");
    myStepperx.step(Location2x);
    mySteppery.step(Location1y);
    myStepperz.step(Locationz);
    mySteppergrab.step(0.1*STEPS);
    delay(200);
    digitalWrite(motorPin, HIGH);
    mySteppergrab.step(-0.1*STEPS);
    digitalWrite(motorPin, LOW);

    Serial.println("counterclockwise");
    myStepperz.step(-Locationz);
    myStepperx.step(-Location2x);
    mySteppery.step(-Location1y);
    mySteppergrab.step(0.1*STEPS);
    mySteppergrab.step(-0.1*STEPS);
    delay(10000);
}

void moveTo5(); {
  Serial.println("clockwise");
    myStepperx.step(Location2x);
    mySteppery.step(Location2y);
    myStepperz.step(Locationz);
    mySteppergrab.step(0.1*STEPS);
    delay(200);
    digitalWrite(motorPin, HIGH);
    mySteppergrab.step(-0.1*STEPS);
    digitalWrite(motorPin, LOW);
    
    Serial.println("counterclockwise");
    myStepperz.step(-Locationz);
    myStepperx.step(-Location2x);
    mySteppery.step(-Location2y);
    mySteppergrab.step(0.1*STEPS);
    mySteppergrab.step(-0.1*STEPS);
    delay(10000);
}

void moveTo6(); {
  Serial.println("clockwise");
    myStepperx.step(Location2x);
    mySteppery.step(Location3y);
    myStepperz.step(Locationz);
    mySteppergrab.step(0.1*STEPS);
    delay(200);
    digitalWrite(motorPin, HIGH);
    mySteppergrab.step(-0.1*STEPS);
    digitalWrite(motorPin, LOW);

    Serial.println("counterclockwise");
    myStepperz.step(-Locationz);
    myStepperx.step(-Location2x);
    mySteppery.step(-Location3y);
    mySteppergrab.step(0.1*STEPS);
    mySteppergrab.step(-0.1*STEPS);
    delay(10000);
}

  void moveTo7(); {
    Serial.println("clockwise");
    myStepperx.step(Location2x);
    mySteppery.step(Location4y);
    myStepperz.step(Locationz);
    mySteppergrab.step(0.1*STEPS);
    delay(200);
    digitalWrite(motorPin, HIGH);
    mySteppergrab.step(-0.1*STEPS);
    delay(200);
    digitalWrite(motorPin, LOW);

    Serial.println("counterclockwise");
    myStepperz.step(-Locationz);
    myStepperx.step(-Location2x);
    mySteppery.step(-Location4y);
    mySteppergrab.step(0.1*STEPS);
    mySteppergrab.step(-0.1*STEPS);
    delay(10000);
}

  void moveTo8();{
    Serial.println("clockwise");
    myStepperx.step(Location3x);
    mySteppery.step(Location1y);
    myStepperz.step(Locationz);
    mySteppergrab.step(0.1*STEPS);
    delay(200);
    digitalWrite(motorPin, HIGH);
    mySteppergrab.step(-0.1*STEPS);
    digitalWrite(motorPin, LOW);

    Serial.println("counterclockwise");
    myStepperz.step(-Locationz);
    myStepperx.step(-Location3x);
    mySteppery.step(-Location1y);
    mySteppergrab.step(0.1*STEPS);
    mySteppergrab.step(-0.1*STEPS);
    delay(10000);
  }
  void MoveTo9(); {
    Serial.println("clockwise");
    myStepperx.step(Location3x);
    mySteppery.step(Location2y);
    myStepperz.step(Locationz);
    mySteppergrab.step(0.1*STEPS);
    delay(200);
    digitalWrite(motorPin, HIGH);
    mySteppergrab.step(-0.1*STEPS);
    digitalWrite(motorPin, LOW);

    Serial.println("counterclockwise");
    myStepperz.step(-Locationz);
    myStepperx.step(-Location3x);
    mySteppery.step(-Location2y);
    mySteppergrab.step(0.1*STEPS);
    mySteppergrab.step(-0.1*STEPS);
    delay(10000);
  }
  
  void MoveTo10(); {
    Serial.println("clockwise");
    myStepperx.step(Location3x);
    mySteppery.step(Location3y);
    myStepperz.step(Locationz);
    mySteppergrab.step(0.1*STEPS);
    delay(200);
    digitalWrite(motorPin, HIGH);
    mySteppergrab.step(-0.1*STEPS);
    digitalWrite(motorPin, LOW);

    Serial.println("counterclockwise");
    myStepperz.step(-Locationz);
    myStepperx.step(-Location3x);
    mySteppery.step(-Location3y);
    mySteppergrab.step(0.1*STEPS);
    mySteppergrab.step(-0.1*STEPS);
    delay(10000);
  }
  
  void MoveTo11(); {
    Serial.println("clockwise");
    myStepperx.step(Location3x);
    mySteppery.step(Location4y);
    myStepperz.step(Locationz);
    mySteppergrab.step(0.1*STEPS);
    delay(200);
    digitalWrite(motorPin, HIGH);
    mySteppergrab.step(-0.1*STEPS);
    digitalWrite(motorPin, LOW);

    Serial.println("counterclockwise");
    myStepperz.step(-Locationz);
    myStepperx.step(-Location3x);
    mySteppery.step(-Location4y);
    mySteppergrab.step(0.1*STEPS);
    mySteppergrab.step(-0.1*STEPS);
    delay(10000);
  }
  
  void MoveTo12(); {
    Serial.println("clockwise");
    myStepperx.step(Location4x);
    mySteppery.step(Location1y);
    myStepperz.step(Locationz);
    mySteppergrab.step(0.1*STEPS);
    delay(200);
    digitalWrite(motorPin, HIGH);
    mySteppergrab.step(-0.1*STEPS);
    digitalWrite(motorPin, LOW);

    Serial.println("counterclockwise");
    myStepperz.step(-Locationz);
    myStepperx.step(-Location4x);
    mySteppery.step(-Location1y);
    mySteppergrab.step(0.1*STEPS);
    mySteppergrab.step(-0.1*STEPS);
    delay(10000);
  }
  
  void MoveTo13(); {
    Serial.println("clockwise");
    myStepperx.step(Location4x);
    mySteppery.step(Location2y);
    myStepperz.step(Locationz);
    mySteppergrab.step(0.1*STEPS);
    delay(200);
    digitalWrite(motorPin, HIGH);
    mySteppergrab.step(-0.1*STEPS);
    digitalWrite(motorPin, LOW);

    Serial.println("counterclockwise");
    myStepperz.step(-Locationz);
    myStepperx.step(-Location4x);
    mySteppery.step(-Location2y);
    mySteppergrab.step(0.1*STEPS);
    mySteppergrab.step(-0.1*STEPS);
    delay(10000);
  }
  
  void MoveTo14(); {
    Serial.println("clockwise");
    myStepperx.step(Location4x);
    mySteppery.step(Location3y);
    myStepperz.step(Locationz);
    mySteppergrab.step(0.1*STEPS);
    delay(200);
    digitalWrite(motorPin, HIGH);
    mySteppergrab.step(-0.1*STEPS);
    digitalWrite(motorPin, LOW);

    Serial.println("counterclockwise");
    myStepperz.step(-Locationz);
    myStepperx.step(-Location4x);
    mySteppery.step(-Location3y);
    mySteppergrab.step(0.1*STEPS);
    mySteppergrab.step(-0.1*STEPS);
    delay(10000);
  }
  
  void MoveTo15(); {
    Serial.println("clockwise");
    myStepperx.step(Location4x);
    mySteppery.step(Location4y);
    myStepperz.step(Locationz);
    mySteppergrab.step(0.1*STEPS);
    delay(200);
    digitalWrite(motorPin, HIGH);
    mySteppergrab.step(-0.1*STEPS);
    digitalWrite(motorPin, LOW);

    Serial.println("counterclockwise");
    myStepperz.step(-Locationz);
    myStepperx.step(-Location4x);
    mySteppery.step(-Location4y);
    mySteppergrab.step(0.1*STEPS);
    mySteppergrab.step(-0.1*STEPS);
    delay(10000);
  }
  
  void MoveTo16(); {
    Serial.println("clockwise");
    myStepperx.step(Location5x);
    mySteppery.step(Location1y);
    myStepperz.step(Locationz);
    mySteppergrab.step(0.1*STEPS);
    delay(200);
    digitalWrite(motorPin, HIGH);
    mySteppergrab.step(-0.1*STEPS);
    digitalWrite(motorPin, LOW);

    Serial.println("counterclockwise");
    myStepperz.step(-Locationz);
    myStepperx.step(-Location5x);
    mySteppery.step(-Location1y);
    mySteppergrab.step(0.1*STEPS);
    mySteppergrab.step(-0.1*STEPS);
    delay(10000);
  }
  
  void MoveTo17(); {
    Serial.println("clockwise");
    myStepperx.step(Location5x);
    mySteppery.step(Location2y);
    myStepperz.step(Locationz);
    mySteppergrab.step(0.1*STEPS);
    delay(200);
    digitalWrite(motorPin, HIGH);
    mySteppergrab.step(-0.1*STEPS);
    digitalWrite(motorPin, LOW);

    Serial.println("counterclockwise");
    myStepperz.step(-Locationz);
    myStepperx.step(-Location5x);
    mySteppery.step(-Location2y);
    mySteppergrab.step(0.1*STEPS);
    mySteppergrab.step(-0.1*STEPS);
    delay(10000);
  }
  void MoveTo18(); {
    Serial.println("clockwise");
    myStepperx.step(Location5x);
    mySteppery.step(Location3y);
    myStepperz.step(Locationz);
    mySteppergrab.step(0.1*STEPS);
    delay(200);
    digitalWrite(motorPin, HIGH);
    mySteppergrab.step(-0.1*STEPS);
    digitalWrite(motorPin, LOW);

    Serial.println("counterclockwise");
    myStepperz.step(-Locationz);
    myStepperx.step(-Location5x);
    mySteppery.step(-Location3y);
    mySteppergrab.step(0.1*STEPS);
    mySteppergrab.step(-0.1*STEPS);
    delay(10000);
  }
  
  void MoveTo19(); {
    Serial.println("clockwise");
    myStepperx.step(Location5x);
    mySteppery.step(Location4y);
    myStepperz.step(Locationz);
    mySteppergrab.step(0.1*STEPS);
    delay(200);
    digitalWrite(motorPin, HIGH);
    mySteppergrab.step(-0.1*STEPS);
    digitalWrite(motorPin, LOW);

    Serial.println("counterclockwise");
    myStepperz.step(-Locationz);
    myStepperx.step(-Location5x);
    mySteppery.step(-Location4y);
    mySteppergrab.step(0.1*STEPS);
    mySteppergrab.step(-0.1*STEPS);
    delay(10000);
  }
}
