#include <LiquidCrystal.h>

#define buzzer 3
#define dark 11

int hours = 0, mins = 0, secs = 0;
unsigned long t;

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

boolean isRepeat = false;

void setup() {
  lcd.begin(16, 2);
  pinMode(buzzer, OUTPUT);
  pinMode(dark, INPUT);
  pinMode(10, OUTPUT);
  lcd.clear();
}

void loop() {
  if (digitalRead(dark == 1)) {
    lcd.setCursor(0, 0);
    lcd.print("Vkluchite lampu");
  }
  t  = millis();
  while (digitalRead(dark) == 0) {
    if (!isRepeat) {
      lcd.clear();
      digitalWrite(10, LOW);
    }
    String time;
    if (hours < 10) {
      time += 0;
    }
    time += hours;
    time += ":";
    if (mins < 10) {
      time += 0;
    }
    time += mins;
    time += ":";
    if (secs < 10) {
      time += 0;
    }
    time += secs;
    if (millis() - t == 1000) {
      secs++;
      t = millis();
      lcd.setCursor(0, 0);
      lcd.print(time);
    }
    if (secs == 60) {
      mins++;
      secs = 0;
    }
    if (mins == 60) {
      hours++;
      mins = 0;
    }
    isRepeat = true;
  }
  if (isRepeat) {
    tone(buzzer, 2000, 1000);
    delay(1500);
    tone(buzzer, 2000, 1000);
    delay(1500);
    tone(buzzer, 2000, 1000);
  }
  while (true) {}
}
