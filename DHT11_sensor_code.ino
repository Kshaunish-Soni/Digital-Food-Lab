#include <dht.h>
#define dataPin 7 // Analog Pin sensor is connected to

//int pin = 6;

dht DHT;
 
void setup(){
 
  //pinMode(pin,OUTPUT);
  Serial.begin(9600);
  delay(500);//Delay to let system boot
  Serial.println("DHT11 Humidity & temperature Sensor\n\n");
  delay(1000);//Wait before accessing Sensor
 
}//end "setup()"
 
void loop(){
  //Start of Program 
  
  //digitalWrite(pin,HIGH);
    int readData = DHT.read22(dataPin);
    
    Serial.print("Current humidity = ");
    Serial.print(DHT.humidity + 7.00);
    Serial.print("%  ");
    Serial.print("temperature = ");
    Serial.print(DHT.temperature - 1.8); 
    Serial.println("C  ");
    
    delay(5000);//Wait 5 seconds before accessing sensor again.
 
  //Fastest should be once every two seconds.
 
}// end loop() 
