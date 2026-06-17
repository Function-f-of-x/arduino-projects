#line 1 "K:\\!!!!Моё\\Arduino\\!Скейчи\\Часы реального времени\\Часы реального времени.ino"
#include <Arduino.h>
#include <DS1307.h>
#include <Wire.h>

DS1307 clock;

#line 7 "K:\\!!!!Моё\\Arduino\\!Скейчи\\Часы реального времени\\Часы реального времени.ino"
void setup();
#line 17 "K:\\!!!!Моё\\Arduino\\!Скейчи\\Часы реального времени\\Часы реального времени.ino"
void loop();
#line 22 "K:\\!!!!Моё\\Arduino\\!Скейчи\\Часы реального времени\\Часы реального времени.ino"
void printDateTime();
#line 65 "K:\\!!!!Моё\\Arduino\\!Скейчи\\Часы реального времени\\Часы реального времени.ino"
String getDayOfWeek();
#line 7 "K:\\!!!!Моё\\Arduino\\!Скейчи\\Часы реального времени\\Часы реального времени.ino"
void setup() {
  Serial.begin(9600);
  clock.begin();
  // clock.fillByYMD(2025, 11, 07);
  // clock.fillByHMS(16, 58, 00);
  // clock.fillDayOfWeek(FRI);
  // clock.setTime();
  clock.startClock();
}

void loop() {
  printDateTime();
  delay(1000);
}

void printDateTime() {
  clock.getTime();
  Serial.print(getDayOfWeek());
  Serial.print(" ");
  if (clock.dayOfMonth < 10) {
    Serial.print("0");
    Serial.print(clock.dayOfMonth);
  } else {
    Serial.print(clock.dayOfMonth);
  }
  Serial.print(".");
  if (clock.month < 10) {
    Serial.print("0");
    Serial.print(clock.month);
  } else {
    Serial.print(clock.month);
  }
  Serial.print(".");
  Serial.print(clock.year + 2000);
  Serial.print("  ");
  if (clock.hour < 10) {
    Serial.print("0");
    Serial.print(clock.hour);
  } else {
    Serial.print(clock.hour);
  }
  Serial.print(":");
  if (clock.minute < 10) {
    Serial.print("0");
    Serial.print(clock.minute);
  } else {
    Serial.print(clock.minute);
  }
  Serial.print(":");
  if (clock.second < 10) {
    Serial.print("0");
    Serial.print(clock.second);
  } else {
    Serial.print(clock.second);
  }
  Serial.println();
}

String getDayOfWeek() {
  switch (clock.dayOfWeek) {
    case MON:
      return " Понедельник";
    case TUE:
      return " Вторник";
    case WED:
      return " Среда";
    case THU:
      return " Четверг";
    case FRI:
      return " Пятница";
    case SAT:
      return " Суббота";
    case SUN:
      return " Воскресенье";
  }
}
