#include <stDHT.h>
DHT sens (DHT11);

void setup() {
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);
  Serial.begin(9600);

}

void loop() {
  int temp = sens.readTemperature(7);
  int hum = sens.readHumidity(7);
  Serial.print("Tемпература:");
  Serial.print(temp);
  Serial.println("℃");
  Serial.print("Влажность:");
  Serial.print(hum);
  Serial.println("%");
  Serial.println();
  delay(1000);
}

