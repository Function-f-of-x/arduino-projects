#include <stDHT.h>
DHT sens (DHT11);

void setup() {
  // put your setup code here, to run once:
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
digitalWrite(7, HIGH);

}

void loop() {
  // put your main code here, to run repeatedly:
  int temp = sens.readTemperature(7);
  int hum = sens.readHumidity(7); 
    
}
