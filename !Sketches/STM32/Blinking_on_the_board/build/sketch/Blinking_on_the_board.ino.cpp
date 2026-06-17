#include <Arduino.h>
#line 1 "C:\\Users\\Klim\\VS Coding\\GitHub\\arduino-projects\\!Sketches\\STM32\\Blinking_on_the_board\\Blinking_on_the_board.ino"
#line 1 "C:\\Users\\Klim\\VS Coding\\GitHub\\arduino-projects\\!Sketches\\STM32\\Blinking_on_the_board\\Blinking_on_the_board.ino"
void setup();
#line 5 "C:\\Users\\Klim\\VS Coding\\GitHub\\arduino-projects\\!Sketches\\STM32\\Blinking_on_the_board\\Blinking_on_the_board.ino"
void loop();
#line 1 "C:\\Users\\Klim\\VS Coding\\GitHub\\arduino-projects\\!Sketches\\STM32\\Blinking_on_the_board\\Blinking_on_the_board.ino"
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}
