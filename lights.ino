const int lights = #;
// # = the digital pin number the lights are plugged in to
void setup() {
  pinMode(lights, OUTPUT);
}

void loop() {
  digitalWrite(lights, HIGH);
  delay(5.76E7);    // 16 hours of light
  digitalWrite(lights, LOW);
  delay(7.2E6);     // 2 hours of dark 
}
