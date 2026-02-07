#include <Arduino.h>
#define LED_PIN PC13

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);  // Скорость как в Uno!
  Serial.println("STM32 READY!");
}

void loop() {
  digitalWrite(LED_PIN, !digitalRead(LED_PIN));
  Serial.print("Hello from C6T6! Counter: ");
  Serial.println(millis() / 1000);
  delay(1000);
}