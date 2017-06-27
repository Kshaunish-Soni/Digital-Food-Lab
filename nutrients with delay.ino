int nutrients = #; // pin number for the nutrients pump 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(nutrients, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(nutrients, HIGH);
  delay(12000); // pump nutrients for 12 seconds
  digitalWrite(nutrients, LOW);
  delay(5.184E8); // pump nutrients every 6 days
}
