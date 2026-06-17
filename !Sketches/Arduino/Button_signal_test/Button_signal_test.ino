#include <LiquidCrystal_1602_RUS.h>

LiquidCrystal_1602_RUS lcd(8, 9, 4, 5 ,6 ,7);

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
}

void loop() {
  lcd.setCursor(0,0);
  lcd.print(analogRead(A0));
  delay(1000);
  lcd.clear();
  delay(100);
  

}
