#include <Arduino.h>
#line 1 "C:\\Users\\Klim\\VS Coding\\GitHub\\arduino-projects\\Arduino\\!Sketches\\stm_test\\stm_test.ino"
#define LED_PIN PC13

#line 3 "C:\\Users\\Klim\\VS Coding\\GitHub\\arduino-projects\\Arduino\\!Sketches\\stm_test\\stm_test.ino"
void setup();
#line 9 "C:\\Users\\Klim\\VS Coding\\GitHub\\arduino-projects\\Arduino\\!Sketches\\stm_test\\stm_test.ino"
void loop();
#line 3 "C:\\Users\\Klim\\VS Coding\\GitHub\\arduino-projects\\Arduino\\!Sketches\\stm_test\\stm_test.ino"
void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
  Serial.println("STM32 ready with ST-Link!");
}

void loop() {
  digitalWrite(LED_PIN, LOW);
  Serial.println("LED ON");
  delay(2000);
  digitalWrite(LED_PIN, HIGH);
  Serial.println("LED OFF");
  delay(2000);
}
