#include <dht.h>
#define dataPin 8 // Analog Pin sensor is connected to

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
    int readData = DHT.read11(dataPin);
    
    Serial.print("Current humidity = ");
    Serial.print(DHT.humidity);
    Serial.print("%  ");
    Serial.print("temperature = ");
    Serial.print(DHT.temperature); 
    Serial.println("C  ");
    
    delay(1000);//Wait 5 seconds before accessing sensor again.
 
  //Fastest should be once every two seconds.
 
}// end loop() 


