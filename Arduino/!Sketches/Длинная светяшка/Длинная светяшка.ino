#include <RemoteXY.h>

byte brightness = 0;

void setup() {
  Serial.begin(9600);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(10, OUTPUT);
}

void loop() {
startLoop:
  delay(500);
  while (true) {
    if (digitalRead(8) == HIGH || digitalRead(7) == HIGH) {
      checkLong();
      brightness = 255;
      analogWrite(10, brightness);
      while (true) {
        if (digitalRead(8) == HIGH || digitalRead(7) == HIGH) {
          checkLong();
          brightness = 128;
          analogWrite(10, brightness);
          while (true) {
            if (digitalRead(8) == HIGH || digitalRead(7) == HIGH) {
              checkLong();
              while (true) {
                analogWrite(10, 255);
                delay(100);
                analogWrite(10, 0);
                delay(100);
                if (digitalRead(8) == HIGH || digitalRead(7) == HIGH) {
                  while (true) {
                    checkLong();
                    SOS();
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}

void checkLong() {
  delay(500);
  if (digitalRead(8) == HIGH || digitalRead(7) == HIGH) {
    delay(1000);
    if (digitalRead(8) == HIGH || digitalRead(7) == HIGH) {
      delay(1500);
      if (digitalRead(8) == HIGH || digitalRead(7) == HIGH) {
        ifLong();
      }
    }
  }
}

void ifLong() {
  brightness = 0;
  while (digitalRead(8) == HIGH || digitalRead(7) == HIGH) {
    while ((digitalRead(8) == HIGH && brightness < 255) || (digitalRead(7) == HIGH && brightness < 255)) {
      brightness++;
      Serial.println(brightness);
      analogWrite(10, brightness);
      delay(20);
    }
    while ((digitalRead(8) == HIGH && brightness > 0) || (digitalRead(7) == HIGH && brightness > 0)) {
      brightness--;
      Serial.println(brightness);
      analogWrite(10, brightness);
      delay(20);
    }
  }
  while (true) {
    if (digitalRead(8) == HIGH || digitalRead(7) == HIGH) {
      loop();
    }
  }
}

void checkSignalOnSOS() {
  if (digitalRead(8) == HIGH || digitalRead(7) == HIGH) {
    loop();
  }
}

void SOS() {
  analogWrite(10, 0);
  checkSignalOnSOS();
  delay(100);
  analogWrite(10, 255);
  checkSignalOnSOS();
  delay(100);
  analogWrite(10, 0);
  checkSignalOnSOS();
  delay(250);
  analogWrite(10, 255);
  checkSignalOnSOS();
  delay(100);
  analogWrite(10, 0);
  checkSignalOnSOS();
  delay(250);
  analogWrite(10, 255);
  checkSignalOnSOS();
  delay(100);
  analogWrite(10, 0);
  checkSignalOnSOS();
  delay(500);
  analogWrite(10, 255);
  checkSignalOnSOS();
  delay(500);
  analogWrite(10, 0);
  checkSignalOnSOS();
  delay(250);
  analogWrite(10, 255);
  checkSignalOnSOS();
  delay(500);
  analogWrite(10, 0);
  checkSignalOnSOS();
  delay(250);
  analogWrite(10, 255);
  checkSignalOnSOS();
  delay(500);
  analogWrite(10, 0);
  checkSignalOnSOS();
  delay(500);
  analogWrite(10, 255);
  checkSignalOnSOS();
  delay(100);
  analogWrite(10, 0);
  checkSignalOnSOS();
  delay(250);
  analogWrite(10, 255);
  checkSignalOnSOS();
  delay(100);
  analogWrite(10, 0);
  checkSignalOnSOS();
  delay(250);
  analogWrite(10, 255);
  checkSignalOnSOS();
  delay(100);
  analogWrite(10, 0);
  checkSignalOnSOS();
  delay(900);
  checkSignalOnSOS();
}