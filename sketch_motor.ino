int sensorPin = 13;
#include <Stepper.h>
int previous = 0;
int timerdelay;
const int STEPS = 200; //change this to fit the numbers
Stepper myStepperx(STEPS, 8, 9, 10, 11);
Stepper mySteppery(STEPS, 2, 3, 4, 5);
Stepper myStepperz(STEPS, 14,15,16,17);
int moveTo0();
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
int moveTo15();

void setup() {
  pinMode(sensorPin, INPUT);
  myStepperx.setSpeed(60);
  mySteppery.setSpeed(60);
  myStepperz.setSpeed(60);
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

void moveTo0(); {
  Serial.println("clockwise");
    myStepperx.step(20*STEPS);
    mySteppery.step(20*STEPS);
    myStepperz.step(30*STEPS);
    delay(200);

    Serial.println("counterclockwise");
    myStepperx.step(previous-20*STEPS);
    mySteppery.step(previous-20*STEPS);
    myStepperz.step(previous-30*STEPS);
    delay(500);
}

void moveTo1(); {
  Serial.println("clockwise");
    myStepperx.step(20*STEPS);
    mySteppery.step(43.35*STEPS);
    myStepperz.step(30*STEPS);
    delay(200);

    Serial.println("counterclockwise");
    myStepperz.step(previous-30*STEPS);
    myStepperx.step(previous-20*STEPS);
    mySteppery.step(previous-43.35*STEPS);
    delay(500);
}

void moveTo2(); {
  Serial.println("clockwise");
    myStepperx.step(20*STEPS);
    mySteppery.step(66.65*STEPS);
    myStepperz.step(30*STEPS);
    delay(200);

    Serial.println("counterclockwise");
    myStepperz.step(previous-30*STEPS);
    myStepperx.step(previous-20*STEPS);
    mySteppery.step(previous-66.65*STEPS);
    delay(500);
}

void moveTo3(); {
  Serial.println("clockwise");
    myStepperx.step(20*STEPS);
    mySteppery.step(90*STEPS);
    myStepperz.step(30*STEPS);
    delay(200);

    Serial.println("counterclockwise");
    myStepperz.step(previous-30*STEPS);
    myStepperx.step(previous-20*STEPS);
    mySteppery.step(previous-90*STEPS);
    delay(500);
}

void moveTo4(); {
  Serial.println("clockwise");
    myStepperx.step(59.15*STEPS);
    mySteppery.step(20*STEPS);
    myStepperz.step(30*STEPS);
    delay(200);

    Serial.println("counterclockwise");
    myStepperz.step(previous-30*STEPS);
    myStepperx.step(previous-59.15*STEPS);
    mySteppery.step(previous-20*STEPS);
    delay(500);
}

void moveTo5(); {
  Serial.println("clockwise");
    myStepperx.step(59.15*STEPS);
    mySteppery.step(43.35*STEPS);
    myStepperz.step(30*STEPS);
    delay(200);

    Serial.println("counterclockwise");
    myStepperz.step(previous-30*STEPS);
    myStepperx.step(previous-59.15*STEPS);
    mySteppery.step(previous-43.35*STEPS);
    delay(500);
}

void moveTo6(); {
  Serial.println("clockwise");
    myStepperx.step(59.15*STEPS);
    mySteppery.step(66.65*STEPS);
    myStepperz.step(30*STEPS);
    delay(200);

    Serial.println("counterclockwise");
    myStepperx.step(previous-59.15*STEPS);
    mySteppery.step(previous-66.65*STEPS);
    myStepperz.step(previous-30*STEPS);
    delay(500);
}

void moveTo7(); {
  Serial.println("clockwise");
    myStepperx.step(59.15*STEPS);
    mySteppery.step(90*STEPS);
    myStepperz.step(30*STEPS);
    delay(200);

    Serial.println("counterclockwise");
    myStepperx.step(previous-59.15*STEPS);
    mySteppery.step(previous-90*STEPS);
    myStepperz.step(previous-30*STEPS);
    delay(500);
}

void moveTo8(); {
  Serial.println("clockwise");
    myStepperx.step(98.3*STEPS);
    mySteppery.step(20*STEPS);
    myStepperz.step(30*STEPS);
    delay(200);

    Serial.println("counterclockwise");
    myStepperz.step(previous-30*STEPS);
    myStepperx.step(previous-98.3*STEPS);
    mySteppery.step(previous-20*STEPS);
    delay(500);
}

void moveTo9(); {
  Serial.println("clockwise");
    myStepperx.step(98.3*STEPS);
    mySteppery.step(43.35*STEPS);
    myStepperz.step(30*STEPS);
    delay(200);

    Serial.println("counterclockwise");
    myStepperz.step(previous-30*STEPS);
    myStepperx.step(previous-98.3*STEPS);
    mySteppery.step(previous-43.35*STEPS);
    delay(500);
}

void moveTo10(); {
  Serial.println("clockwise");
    myStepperx.step(98.3*STEPS);
    mySteppery.step(66.65*STEPS);
    myStepperz.step(30*STEPS);
    delay(200);

    Serial.println("counterclockwise");
    myStepperz.step(previous-30*STEPS);
    myStepperx.step(previous-98.3*STEPS);
    mySteppery.step(previous-66.65*STEPS);
    delay(500);
}

void moveTo11(); {
  Serial.println("clockwise");
    myStepperx.step(98.3*STEPS);
    mySteppery.step(90*STEPS);
    myStepperz.step(30*STEPS);
    delay(200);

    Serial.println("counterclockwise");
    myStepperz.step(previous-30*STEPS);
    myStepperx.step(previous-98.3*STEPS);
    mySteppery.step(previous-90*STEPS);
    delay(500);
}

void moveTo12(); {
  Serial.println("clockwise");
    myStepperx.step(137.5*STEPS);
    mySteppery.step(20*STEPS);
    myStepperz.step(30*STEPS);
    delay(200);

    Serial.println("counterclockwise");
    myStepperz.step(previous-30*STEPS);
    myStepperx.step(previous-137.5*STEPS);
    mySteppery.step(previous-20*STEPS);
    delay(500);
}

void moveTo13(); {
  Serial.println("clockwise");
    myStepperx.step(137.5*STEPS);
    mySteppery.step(43.35*STEPS);
    myStepperz.step(30*STEPS);
    delay(200);

    Serial.println("counterclockwise");
    myStepperz.step(previous-30*STEPS);
    myStepperx.step(previous-137.5*STEPS);
    mySteppery.step(previous-43.35*STEPS);
    delay(500);
}

void moveTo14(); {
  Serial.println("clockwise");
    myStepperx.step(137.5*STEPS);
    mySteppery.step(66.65*STEPS);
    myStepperz.step(30*STEPS);
    delay(200);

    Serial.println("counterclockwise");
    myStepperz.step(previous-30*STEPS);
    myStepperx.step(previous-137.5*STEPS);
    mySteppery.step(previous-66.65*STEPS);
    delay(500);
}

void moveTo15(); {
  Serial.println("clockwise");
    myStepperx.step(137.5*STEPS);
    mySteppery.step(90*STEPS);
    myStepperz.step(30*STEPS);
    delay(200);

    Serial.println("counterclockwise");
    myStepperx.step(previous-137.5*STEPS);
    mySteppery.step(previous-90*STEPS);
    myStepperz.step(previous-30*STEPS);
    delay(500);
}

}

