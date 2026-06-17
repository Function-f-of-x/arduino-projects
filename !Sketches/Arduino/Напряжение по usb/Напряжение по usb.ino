#include <LiquidCrystal_1602_RUS.h>

const byte RIGHT = 0, UP = 1, DOWN = 2, LEFT = 3, SELECT = 4, NONE = 5;
boolean isRepeat = false;

LiquidCrystal_1602_RUS lcd(8, 9, 4, 5, 6, 7);

byte getKey() {
  if (analogRead(A0) < 50) return RIGHT; 
  else if (analogRead(A0) < 150) return UP; 
  else if (analogRead(A0) < 350) return DOWN; 
  else if (analogRead(A0) < 550) return LEFT;
  else if (analogRead(A0) < 750) return SELECT; 
  else if (analogRead(A0) <= 1023) return NONE;
}

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
}

void loop() {
  if (!isRepeat) {
    lcd.print(L"Горячие клавиши:");
    delay(1000);
    lcd.clear();
    lcd.print(L"SELECT - peжиm:");
    lcd.setCursor(1, 1);
    lcd.print(L"Подсветк./напр.");
    delay(4000);
    lcd.clear();
    lcd.setCursor(0, 2);
    lcd.print("LEFT/RIGHT -");
    lcd.setCursor(1, 3);
    lcd.print("меньше/больше");
  } 
  
}
