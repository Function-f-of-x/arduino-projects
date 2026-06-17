#include <Wire.h>
#include <DS1307.h>

DS1307 rtc; // Создаем объект для работы с DS1307

void setup() {
  Serial.begin(9600);
  Wire.begin();
  rtc.begin();
  rtc.fillByYMD(2025, 04, 30);
  rtc.fillByHMS(19, 05, 0);
  rtc.fillDayOfWeek(3);
  // rtc.setTime();
  rtc.startClock();
}

void loop() {
  rtc.getTime();
  Serial.print(getDayOfWeek() + " ");
  char dateBuf[21];
  sprintf(dateBuf, "%02d.%02d.%d", rtc.dayOfMonth, rtc.month, rtc.year + 2000);
  String date(dateBuf);
  Serial.print(date + " ");
  char timeBuf[21];
  sprintf(timeBuf, "%02d:%02d:%02d", rtc.hour, rtc.minute, rtc.second);
  String time(timeBuf);
  Serial.println(time);
  delay(1000); // Обновление каждую секунду
}

String getDayOfWeek() {
  switch (rtc.dayOfWeek) {
    case MON:
      return "Pn";
    case TUE:
      return "Vt";
    case WED:
      return "Sr";
    case THU:
      return "Cht";
    case FRI:
      return "Pt";
    case SAT:
      return "Sb";
    case SUN:
      return "Vs";
  }
}