#include <stDHT.h>
DHT sens (DHT11);
unsigned long t;

void setup() {
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);
  Serial.begin(9600);

}

void loop() {
  int temp = sens.readTemperature(7);
  int hum = sens.readHumidity(7);
  if (millis() - t > 10000) {
  t = millis();
  Serial.print("Tемпература:");
  Serial.print(temp);
  Serial.println("℃");
  Serial.print("Влажность:");
  Serial.print(hum);
  Serial.println("%");
  Serial.println();
  }
}
