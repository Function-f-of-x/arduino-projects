#line 1 "K:\\!!!!Моё\\Arduino\\!Скейчи\\Test_VS_code_\\Test_VS_code_.ino"
#include <Arduino.h>

#line 3 "K:\\!!!!Моё\\Arduino\\!Скейчи\\Test_VS_code_\\Test_VS_code_.ino"
void setup();
#line 8 "K:\\!!!!Моё\\Arduino\\!Скейчи\\Test_VS_code_\\Test_VS_code_.ino"
void loop();
#line 3 "K:\\!!!!Моё\\Arduino\\!Скейчи\\Test_VS_code_\\Test_VS_code_.ino"
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

