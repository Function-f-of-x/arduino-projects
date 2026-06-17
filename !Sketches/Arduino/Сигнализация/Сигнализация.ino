#include <Ultrasonic.h>
#define buzzer 8

Ultrasonic ultrasonic(7, 11);
int distance;

void setup() {
  pinMode(buzzer, OUTPUT);
}

void loop() {
  distance = ultrasonic.read();
  
  if (distance <= 50) {
    tone(buzzer, 2000, 150);
    int zaderzhka = distance * 10;
    if (distance < 5) {
      zaderzhka = 0;
    }
    delay(zaderzhka);
  }
}
