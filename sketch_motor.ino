
int sensorPin = 13;
int motorPin = 2;
#include <Stepper.h>
int previous = 0;
int timerdelay;
const int STEPS = 200; //change this to fit the numbers
Stepper myStepperx(STEPS, 8, 9);
Stepper mySteppery(STEPS, 10, 11);
Stepper myStepperz(STEPS, 6, 7);
Stepper mySteppergrab(STEPS, 12, 13);
int moveTo0();
int moveTo1();
int moveTo2();
int moveTo3();
int moveTo4();
int moveTo5();
int moveTo6();

void setup() {
  pinMode(sensorPin, INPUT);
  myStepperx.setSpeed(200);
  mySteppery.setSpeed(200);
  myStepperz.setSpeed(100);
  mySteppergrab.setSpeed(60);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int val = analogRead(0);
  if (sensorPin, val=0)
  {
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

void moveTo0(); {
  Serial.println("clockwise");
    myStepperx.step(12.5*STEPS);
    mySteppery.step(72.5*STEPS);
    delay(100);
    mySteppergrab.step(0.25*STEPS);
    myStepperz.step(15*STEPS);
    delay(200);
    digitalWrite(motorPin, HIGH);
    mySteppergrab.step(-0.25*STEPS);
    
    Serial.println("counterclockwise");
    myStepperz.step(previous-15*STEPS);
    delay(100);
    myStepperx.step(previous-12.5*STEPS);
    mySteppery.step(previous-72.5*STEPS);
    delay(10000);

    
}

void moveTo1(); {
  Serial.println("clockwise");
    myStepperx.step(12.5*STEPS);
    mySteppery.step(52.5*STEPS);
    delay(100);
    mySteppergrab.step(0.25*STEPS);
    myStepperz.step(15*STEPS);
    delay(200);]
    digitalWrite(motorPin, HIGH);
    mySteppergrab.step(-0.25*STEPS);
    digitalWrite(motorPin, LOW);

    Serial.println("counterclockwise");
    myStepperz.step(previous-15*STEPS);
    delay(100);
    myStepperx.step(previous-12.5*STEPS);
    mySteppery.step(previous-52.5*STEPS);
    delay(10000);
}

void moveTo2(); {
  Serial.println("clockwise");
    myStepperx.step(32.5*STEPS);
    mySteppery.step(32.5*STEPS);
    myStepperz.step(15*STEPS);
    mySteppergrab.step(0.25*STEPS);
    delay(200);
    digitalWrite(motorPin, HIGH);
    mySteppergrab.step(-0.25*STEPS);
    digitalWrite(motorPin, LOW);

    Serial.println("counterclockwise");
    myStepperz.step(previous-15*STEPS);
    myStepperx.step(previous-32.5*STEPS);
    mySteppery.step(previous-32.5*STEPS);
    mySteppergrab.step(-0.25*STEPS);
    delay(10000);
}

void moveTo3(); {
  Serial.println("clockwise");
    myStepperx.step(52.5*STEPS);
    mySteppery.step(12.5*STEPS);
    myStepperz.step(15*STEPS);
    mySteppergrab.step(0.25*STEPS);
    delay(200);
    digitalWrite(motorPin, HIGH);
    mySteppergrab.step(-0.25*STEPS);
    digitalWrite(motorPin, LOW);

    Serial.println("counterclockwise");
    myStepperz.step(previous-15*STEPS);
    myStepperx.step(previous-52.5*STEPS);
    mySteppery.step(previous-12.5*STEPS);
    mySteppergrab.step(-0.25*STEPS);
    delay(10000);
}
 
void moveTo4(); {
  Serial.println("clockwise");
    myStepperx.step(72.5*STEPS);
    mySteppery.step(32.5*STEPS);
    myStepperz.step(15*STEPS);
    mySteppergrab.step(0.25*STEPS);
    delay(200);
    digitalWrite(motorPin, HIGH);
    mySteppergrab.step(-0.25*STEPS);
    digitalWrite(motorPin, LOW);

    Serial.println("counterclockwise");
    myStepperz.step(previous-15*STEPS);
    myStepperx.step(previous-72.5*STEPS);
    mySteppery.step(previous-32.5*STEPS);
    mySteppergrab.step(-0.25*STEPS);
    delay(10000);
}

void moveTo5(); {
  Serial.println("clockwise");
    myStepperx.step(72.5*STEPS);
    mySteppery.step(72.5*STEPS);
    myStepperz.step(15*STEPS);
    mySteppergrab.step(0.25*STEPS);
    delay(200);
    digitalWrite(motorPin, HIGH);
    mySteppergrab.step(-0.25*STEPS);
    digitalWrite(motorPin, LOW);
    
    Serial.println("counterclockwise");
    myStepperz.step(previous-15*STEPS);
    myStepperx.step(previous-72.5*STEPS);
    mySteppery.step(previous-72.5*STEPS);
    mySteppergrab.step(-0.25*STEPS);
    delay(10000);
}

void moveTo6(); {
  Serial.println("clockwise");
    myStepperx.step(92.5*STEPS);
    mySteppery.step(52.5*STEPS);
    myStepperz.step(15*STEPS);
    mySteppergrab.step(0.25*STEPS);
    delay(200);
    digitalWrite(motorPin, HIGH);
    mySteppergrab.step(-0.25*STEPS);
    digitalWrite(motorPin, LOW);

    Serial.println("counterclockwise");
    myStepperx.step(previous-92.5*STEPS);
    mySteppery.step(previous-52.5*STEPS);
    myStepperz.step(previous-15*STEPS);
    mySteppergrab.step(-0.25*STEPS);
    delay(10000);
}

}

  
