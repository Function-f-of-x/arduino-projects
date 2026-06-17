#include <Arduino.h>
#line 1 "C:\\Users\\Klim\\VS Coding\\GitHub\\arduino-projects\\!Sketches\\STM32\\stm_test\\stm_test.ino"
#line 1 "C:\\Users\\Klim\\VS Coding\\GitHub\\arduino-projects\\!Sketches\\STM32\\stm_test\\stm_test.ino"
void setup();
#line 7 "C:\\Users\\Klim\\VS Coding\\GitHub\\arduino-projects\\!Sketches\\STM32\\stm_test\\stm_test.ino"
void loop();
#line 1 "C:\\Users\\Klim\\VS Coding\\GitHub\\arduino-projects\\!Sketches\\STM32\\stm_test\\stm_test.ino"
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  Serial.println("IT WORKS!!!!!!!!");
}

void loop() {
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
}
