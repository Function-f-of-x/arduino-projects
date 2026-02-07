#include <Arduino.h>

void setup() {
    pinMode(13, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    digitalWrite(13, HIGH);
    delay(1000); // Delay for 1000 milliseconds
    digitalWrite(13, LOW);
    delay(1000); // Delay for 1000 milliseconds
    Serial.println("One loop done");
}
