#include <LiquidCrystal_1602_RUS.h>

const byte RIGHT = 0, UP = 1, DOWN = 2, LEFT = 3, SELECT = 4, NONE = 5;

byte counter = 0;

LiquidCrystal_1602_RUS lcd(8, 9, 4, 5, 6, 7);

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
    lcd.print(L"Кликай на кнопки");
    lcd.setCursor(3, 1);
    lcd.print(L"UP и DOWN");
    lcd.clear();
}

byte getKey() {
  if (analogRead(A0) < 50) return RIGHT; 
  else if (analogRead(A0) < 150) return UP; 
  else if (analogRead(A0) < 350) return DOWN; 
  else if (analogRead(A0) < 550) return LEFT;
  else if (analogRead(A0) < 750) return SELECT; 
  else if (analogRead(A0) <= 1023) return NONE;
}

void loop() {
  if (counter == 0) {
    
  }
  if (counter == 1) {
    lcd.setCursor(0, 0);
    lcd.print(L"С восьмым марта!");
    delay(500);
    if (getKey() == UP) {
       counter--;
       lcd.clear();
    }
    if (getKey() == DOWN) {
       counter++;
       lcd.clear();
    }
  }
  if (counter == 2) {
    lcd.setCursor(0, 0);
    lcd.print(L"Ты лучшая мамоч-");
    lcd.setCursor(7, 1);
    lcd.print(L"ка!");
    delay(500);
    if (getKey() == UP) {
       counter--;
       lcd.clear();
    }
    if (getKey() == DOWN) {
       counter++;
       lcd.clear();
    }
  }
  if (counter == 3) {
    lcd.setCursor(0, 0);
    lcd.print(L"Тебе понравился");
    lcd.setCursor(4, 1);
    lcd.print(L"подарок?");
    delay(500);
    if (getKey() == UP) {
       counter--;
       lcd.clear();
    }
    if (getKey() == DOWN) {
       counter++;
       lcd.clear();
    }
  }
  if (counter == 4) {
    lcd.setCursor(0, 0);
    lcd.print(L"А идея с диспле-");
    lcd.setCursor(7, 1);
    lcd.print(L"ем?");
    delay(500);
    if (getKey() == UP) {
       counter--;
       lcd.clear();
    }
    if (getKey() == DOWN) {
       counter++;
       lcd.clear();
    }
  }
  if (counter == 5) {
    lcd.setCursor(3, 0);
    lcd.print(L"Спасибо!!!");;
    delay(500);
    if (getKey() == UP) {
       counter--;
       lcd.clear();
    }
    if (getKey() == DOWN) {
       counter++;
       lcd.clear();
    }
  }
  if (counter == 6) {
    lcd.setCursor(0, 0);
    lcd.print(L"Ты лучшая мамоч-");
    lcd.setCursor(6, 1);
    lcd.print(L"ка!!!");
    delay(500);
    if (getKey() == UP) {
       counter--;
       lcd.clear();
    }
    if (getKey() == DOWN) {
       counter++;
       lcd.clear();
    }
  }
}
