#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

byte hour, minute, second;

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
}

void loop() {
  char time[11];
  second = millis() / 1000;
  minute = second / 60;
  hour = minute / 24;
  minute = minute > 59 ? 0 : minute;
  second = second > 59 ? 0 : second;
  sprintf(time, "%02d:%02d:%02d", hour, minute, second);
  lcd.setCursor(0, 0);
  lcd.print("Svet vkluchili");
  lcd.setCursor(2, 1);
  lcd.print(time);
  lcd.print(" nazad");
}
