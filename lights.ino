const int lights = #;
// # = the digital pin number the lights are plugged in to
void setup() {
  // put your setup code here, to run once:
  pinMode(lights, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(lights, HIGH);
  delay(5.76E7);    // 16 hours of light
  digitalWrite(lights, LOW);
  delay(7.2E6);     // 2 hours of dark 
}
