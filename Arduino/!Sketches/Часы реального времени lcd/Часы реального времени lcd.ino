#include <DS1307.h>
#include <Wire.h>
#include <LiquidCrystal.h>

DS1307 clock;
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

const byte RIGHT = 0, UP = 1, DOWN = 2, LEFT = 3, SELECT = 4, NONE = 5;

int day1, day2, month1, month2, year1, year2, year3, year4, hour1, hour2, minute1, minute2, second1, second2;
int day, month, year, hour, minute, second;
int dateCursor, timeCursor;
int dayOfWeek;

short brightness = 255;

byte getKey() {
  if (analogRead(A0) < 50) return RIGHT;
  else if (analogRead(A0) < 150) return UP;
  else if (analogRead(A0) < 350) return DOWN;
  else if (analogRead(A0) < 550) return LEFT;
  else if (analogRead(A0) < 750) return SELECT;
  else if (analogRead(A0) <= 1023) return NONE;
}

void setup() {
  pinMode(10, OUTPUT);
  analogWrite(10, 255);
  lcd.begin(16, 2);
  clock.begin();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SELECT: Izmenit'");
  lcd.setCursor(0, 1);
  lcd.print("datu/vrem'a");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("UP/DOWN: Izme-");
  lcd.setCursor(0, 1);
  lcd.print("nit' yarkost'");
  delay(3000);
  lcd.clear();
}

void loop() {
  printDateTime();
  if (getKey() == SELECT) {
    setDateTime();
  }
  if (getKey() == UP) {
    lcd.clear();
    while (getKey() == UP) {
      if (brightness != 255) {
        brightness++;
      }
      delay(50);
      lcd.setCursor(0, 0);
      lcd.print("Yarkost': ");
      if (brightness < 10) {
        lcd.print("00");
        lcd.print(brightness);
      } else if (brightness < 100) {
        lcd.print("0");
        lcd.print(brightness);
      } else {
        lcd.print(brightness);
      }
      analogWrite(10, brightness);
    }
    delay(1000);
    lcd.clear();
  }
  if (getKey() == DOWN) {
    lcd.clear();
    while (getKey() == DOWN) {
      if (brightness != 0) {
        brightness--;
      }
      delay(50);
      lcd.setCursor(0, 0);
      lcd.print("Yarkost': ");
      if (brightness < 10) {
        lcd.print("00");
        lcd.print(brightness);
      } else if (brightness < 100) {
        lcd.print("0");
        lcd.print(brightness);
      } else {
        lcd.print(brightness);
      }
      analogWrite(10, brightness);
    }
    delay(1000);
    lcd.clear();
  }
}

void printDateTime() {
  clock.getTime();
  lcd.setCursor(0, 0);
  lcd.print(getDayOfWeek());
  lcd.print(" ");
  char date[16];
  sprintf(date, "%02d.%02d.%d", clock.dayOfMonth, clock.month, clock.year + 2000);
  lcd.print(date);
  lcd.setCursor(0, 1);
  char time[11];
  sprintf(time, "%02d:%02d:%02d", clock.hour, clock.minute, clock.second);
  lcd.print(time);
}

void setDateTime() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SELECT: Ustano-");
  lcd.setCursor(0, 1);
  lcd.print("vit' datu/vrem'a");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("UP/DOWN: Men'at'");
  lcd.setCursor(0, 1);
  lcd.print("tsifru");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("LEFT/RIGHT: Pere");
  lcd.setCursor(0, 1);
  lcd.print("kluchat' tsifru");
  delay(3000);
  lcd.clear();
  lcd.setCursor(6, 0);
  lcd.print("Data");
  lcd.setCursor(3, 1);
  lcd.print("DD.MM.YYYY");
  delay(1000);
  while (true) {
    switch (dateCursor) {
      case 0:
        lcd.setCursor(6, 0);
        lcd.print("Data");
        lcd.setCursor(3, 1);
        printDate();
        delay(50);
        lcd.setCursor(3, 1);
        lcd.print(" ");
        delay(50);
        if (getKey() == UP) {
          if (day1 < 9) {
            day1 += 1;
            delay(500);
          } else {
            day1 = 0;
            delay(500);
          }
        }
        if (getKey() == DOWN) {
          if (day1 > 0) {
            day1 -= 1;
            delay(500);
          } else {
            day1 = 9;
            delay(500);
          }
        }
        if (getKey() == RIGHT) {
          dateCursor++;
          delay(500);
        }
        if (getKey() == SELECT) {
          goto dateSetted;
        }
        break;
      case 1:
        lcd.setCursor(6, 0);
        lcd.print("Data");
        lcd.setCursor(3, 1);
        printDate();
        delay(50);
        lcd.setCursor(4, 1);
        lcd.print(" ");
        delay(50);
        if (getKey() == UP) {
          if (day2 < 9) {
            day2 += 1;
            delay(500);
          } else {
            day2 = 0;
            delay(500);
          }
        }
        if (getKey() == DOWN) {
          if (day2 > 0) {
            day2 -= 1;
            delay(500);
          } else {
            day2 = 9;
            delay(500);
          }
        }
        if (getKey() == LEFT) {
          dateCursor--;
          delay(500);
        }
        if (getKey() == RIGHT) {
          dateCursor++;
          delay(500);
        }
        if (getKey() == SELECT) {
          goto dateSetted;
        }
        break;
      case 2:
        lcd.setCursor(6, 0);
        lcd.print("Data");
        lcd.setCursor(3, 1);
        printDate();
        delay(50);
        lcd.setCursor(6, 1);
        lcd.print(" ");
        delay(50);
        if (getKey() == UP) {
          if (month1 < 9) {
            month1 += 1;
            delay(500);
          } else {
            month1 = 0;
            delay(500);
          }
        }
        if (getKey() == DOWN) {
          if (month1 > 0) {
            month1 -= 1;
            delay(500);
          } else {
            month1 = 9;
            delay(500);
          }
        }
        if (getKey() == LEFT) {
          dateCursor--;
          delay(500);
        }
        if (getKey() == RIGHT) {
          dateCursor++;
          delay(500);
        }
        if (getKey() == SELECT) {
          goto dateSetted;
        }
        break;
      case 3:
        lcd.setCursor(6, 0);
        lcd.print("Data");
        lcd.setCursor(3, 1);
        printDate();
        delay(50);
        lcd.setCursor(7, 1);
        lcd.print(" ");
        delay(50);
        if (getKey() == UP) {
          if (month2 < 9) {
            month2 += 1;
            delay(500);
          } else {
            month2 = 0;
            delay(500);
          }
        }
        if (getKey() == DOWN) {
          if (month2 > 0) {
            month2 -= 1;
            delay(500);
          } else {
            month2 = 9;
            delay(500);
          }
        }
        if (getKey() == LEFT) {
          dateCursor--;
          delay(500);
        }
        if (getKey() == RIGHT) {
          dateCursor++;
          delay(500);
        }
        if (getKey() == SELECT) {
          goto dateSetted;
        }
        break;
      case 4:
        lcd.setCursor(6, 0);
        lcd.print("Data");
        lcd.setCursor(3, 1);
        printDate();
        delay(50);
        lcd.setCursor(9, 1);
        lcd.print(" ");
        delay(50);
        if (getKey() == UP) {
          if (year1 < 9) {
            year1 += 1;
            delay(500);
          } else {
            year1 = 0;
            delay(500);
          }
        }
        if (getKey() == DOWN) {
          if (year1 > 0) {
            year1 -= 1;
            delay(500);
          } else {
            year1 = 9;
            delay(500);
          }
        }
        if (getKey() == LEFT) {
          dateCursor--;
          delay(500);
        }
        if (getKey() == RIGHT) {
          dateCursor++;
          delay(500);
        }
        if (getKey() == SELECT) {
          goto dateSetted;
        }
        break;
      case 5:
        lcd.setCursor(6, 0);
        lcd.print("Data");
        lcd.setCursor(3, 1);
        printDate();
        delay(50);
        lcd.setCursor(10, 1);
        lcd.print(" ");
        delay(50);
        if (getKey() == UP) {
          if (year2 < 9) {
            year2 += 1;
            delay(500);
          } else {
            year2 = 0;
            delay(500);
          }
        }
        if (getKey() == DOWN) {
          if (year2 > 0) {
            year2 -= 1;
            delay(500);
          } else {
            year2 = 9;
            delay(500);
          }
        }
        if (getKey() == LEFT) {
          dateCursor--;
          delay(500);
        }
        if (getKey() == RIGHT) {
          dateCursor++;
          delay(500);
        }
        if (getKey() == SELECT) {
          goto dateSetted;
        }
        break;
      case 6:
        lcd.setCursor(6, 0);
        lcd.print("Data");
        lcd.setCursor(3, 1);
        printDate();
        delay(50);
        lcd.setCursor(11, 1);
        lcd.print(" ");
        delay(50);
        if (getKey() == UP) {
          if (year3 < 9) {
            year3 += 1;
            delay(500);
          } else {
            year3 = 0;
            delay(500);
          }
        }
        if (getKey() == DOWN) {
          if (year3 > 0) {
            year3 -= 1;
            delay(500);
          } else {
            year3 = 9;
            delay(500);
          }
        }
        if (getKey() == LEFT) {
          dateCursor--;
          delay(500);
        }
        if (getKey() == RIGHT) {
          dateCursor++;
          delay(500);
        }
        if (getKey() == SELECT) {
          goto dateSetted;
        }
        break;
      case 7:
        lcd.setCursor(6, 0);
        lcd.print("Data");
        lcd.setCursor(3, 1);
        printDate();
        delay(50);
        lcd.setCursor(12, 1);
        lcd.print(" ");
        delay(50);
        if (getKey() == UP) {
          if (year4 < 9) {
            year4 += 1;
            delay(500);
          } else {
            year4 = 0;
            delay(500);
          }
        }
        if (getKey() == DOWN) {
          if (year4 > 0) {
            year4 -= 1;
            delay(500);
          } else {
            year4 = 9;
            delay(500);
          }
        }
        if (getKey() == LEFT) {
          dateCursor--;
          delay(500);
        }
        if (getKey() == SELECT) {
          goto dateSetted;
        }
        break;
    }
  }
dateSetted:
  delay(500);
  clock.setTime();
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("Vrem'a");
  lcd.setCursor(4, 1);
  lcd.print("HH:MM:SS");
  delay(1000);
  while (true) {
    switch (timeCursor) {
      case 0:
        lcd.setCursor(5, 0);
        lcd.print("Vrem'a");
        lcd.setCursor(4, 1);
        printTime();
        delay(50);
        lcd.setCursor(4, 1);
        lcd.print(" ");
        delay(50);
        if (getKey() == UP) {
          if (hour1 < 9) {
            hour1 += 1;
            delay(500);
          } else {
            hour1 = 0;
            delay(500);
          }
        }
        if (getKey() == DOWN) {
          if (hour1 > 0) {
            hour1 -= 1;
            delay(500);
          } else {
            hour1 = 9;
            delay(500);
          }
        }
        if (getKey() == RIGHT) {
          timeCursor++;
          delay(500);
        }
        if (getKey() == SELECT) {
          setTime();
          goto timeSetted;
        }
        break;
      case 1:
        lcd.setCursor(5, 0);
        lcd.print("Vrem'a");
        lcd.setCursor(4, 1);
        printTime();
        delay(50);
        lcd.setCursor(5, 1);
        lcd.print(" ");
        delay(50);
        if (getKey() == UP) {
          if (hour2 < 9) {
            hour2 += 1;
            delay(500);
          } else {
            hour2 = 0;
            delay(500);
          }
        }
        if (getKey() == DOWN) {
          if (hour2 > 0) {
            hour2 -= 1;
            delay(500);
          } else {
            hour2 = 9;
            delay(500);
          }
        }
        if (getKey() == LEFT) {
          timeCursor--;
          delay(500);
        }
        if (getKey() == RIGHT) {
          timeCursor++;
          delay(500);
        }
        if (getKey() == SELECT) {
          setTime();
          goto timeSetted;
        }
        break;
      case 2:
        lcd.setCursor(5, 0);
        lcd.print("Vrem'a");
        lcd.setCursor(4, 1);
        printTime();
        delay(50);
        lcd.setCursor(7, 1);
        lcd.print(" ");
        delay(50);
        if (getKey() == UP) {
          if (minute1 < 9) {
            minute1 += 1;
            delay(500);
          } else {
            minute1 = 0;
            delay(500);
          }
        }
        if (getKey() == DOWN) {
          if (minute1 > 0) {
            minute1 -= 1;
            delay(500);
          } else {
            minute1 = 9;
            delay(500);
          }
        }
        if (getKey() == LEFT) {
          timeCursor--;
          delay(500);
        }
        if (getKey() == RIGHT) {
          timeCursor++;
          delay(500);
        }
        if (getKey() == SELECT) {
          setTime();
          goto timeSetted;
        }
        break;
      case 3:
        lcd.setCursor(5, 0);
        lcd.print("Vrem'a");
        lcd.setCursor(4, 1);
        printTime();
        delay(50);
        lcd.setCursor(8, 1);
        lcd.print(" ");
        delay(50);
        if (getKey() == UP) {
          if (minute2 < 9) {
            minute2 += 1;
            delay(500);
          } else {
            minute2 = 0;
            delay(500);
          }
        }
        if (getKey() == DOWN) {
          if (minute2 > 0) {
            minute2 -= 1;
            delay(500);
          } else {
            minute2 = 9;
            delay(500);
          }
        }
        if (getKey() == LEFT) {
          timeCursor--;
          delay(500);
        }
        if (getKey() == RIGHT) {
          timeCursor++;
          delay(500);
        }
        if (getKey() == SELECT) {
          setTime();
          goto timeSetted;
        }
        break;
      case 4:
        lcd.setCursor(5, 0);
        lcd.print("Vrem'a");
        lcd.setCursor(4, 1);
        printTime();
        delay(50);
        lcd.setCursor(10, 1);
        lcd.print(" ");
        delay(50);
        if (getKey() == UP) {
          if (second1 < 9) {
            second1 += 1;
            delay(500);
          } else {
            second1 = 0;
            delay(500);
          }
        }
        if (getKey() == DOWN) {
          if (second1 > 0) {
            second1 -= 1;
            delay(500);
          } else {
            second1 = 9;
            delay(500);
          }
        }
        if (getKey() == LEFT) {
          timeCursor--;
          delay(500);
        }
        if (getKey() == RIGHT) {
          timeCursor++;
          delay(500);
        }
        if (getKey() == SELECT) {
          setTime();
          goto timeSetted;
        }
        break;
      case 5:
        lcd.setCursor(5, 0);
        lcd.print("Vrem'a");
        lcd.setCursor(4, 1);
        printTime();
        delay(50);
        lcd.setCursor(11, 1);
        lcd.print(" ");
        delay(50);
        if (getKey() == UP) {
          if (second2 < 9) {
            second2 += 1;
            delay(500);
          } else {
            second2 = 0;
            delay(500);
          }
        }
        if (getKey() == DOWN) {
          if (second2 > 0) {
            second2 -= 1;
            delay(500);
          } else {
            second2 = 9;
            delay(500);
          }
        }
        if (getKey() == LEFT) {
          timeCursor--;
          delay(500);
        }
        if (getKey() == SELECT) {
          goto timeSetted;
        }
        break;
    }
  }
timeSetted:
  //   delay(500);
  //   lcd.clear();
  //   while (true) {
  //     lcd.setCursor(2, 0);
  //     lcd.print("Den' nedeli");
  //     lcd.setCursor(10, 1);
  //     lcd.print(dayOfWeek + 1);
  //     lcd.print(" ");
  //     lcd.print(getSketchDOW());
  //     if (getKey() == UP) {
  //       if (dayOfWeek == 3) {
  //         lcd.setCursor(14, 1);
  //         lcd.print(" ");
  //       }
  //       if (dayOfWeek < 6) {
  //         dayOfWeek += 1;
  //         delay(500);
  //       } else {
  //         dayOfWeek = 0;
  //         delay(500);
  //       }
  //     }
  //     if (getKey() == DOWN) {
  //       if (dayOfWeek == 3) {
  //         lcd.setCursor(14, 1);
  //         lcd.print(" ");
  //       }
  //       if (dayOfWeek > 0) {
  //         dayOfWeek -= 1;
  //         delay(500);
  //       } else {
  //         dayOfWeek = 6;
  //         delay(500);
  //       }
  //     }
  //     if (getKey() == SELECT) {
  //       goto DOWSetted;
  //     }
  //   }
  // DOWSetted:
  byte shift[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
  if (month < 3) {
    year--;
    dayOfWeek = ((year + year / 4 - year / 100 + year / 400 + shift[month - 1] + day) % 7) + 1;
    year++;
  } else {
    dayOfWeek = ((year + year / 4 - year / 100 + year / 400 + shift[month - 1] + day) % 7) + 1;
  }
  delay(500);
  byte DS = setDate();
  byte TS = setTime();
  if (DS == 0) {
    clock.fillByYMD(year, month, day);
  }
  if (TS == 0) {
    clock.fillByHMS(hour, minute, second);
  }
  clock.fillDayOfWeek(dayOfWeek + 1);
  clock.setTime();
  reseetAllVariables();
  lcd.clear();
}

String getDayOfWeek() {
  switch (clock.dayOfWeek) {
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

String getSketchDOW() {
  switch (dayOfWeek + 1) {
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


void printDate() {
  lcd.print(day1);
  lcd.print(day2);
  lcd.print(".");
  lcd.print(month1);
  lcd.print(month2);
  lcd.print(".");
  lcd.print(year1);
  lcd.print(year2);
  lcd.print(year3);
  lcd.print(year4);
}

void printTime() {
  lcd.print(hour1);
  lcd.print(hour2);
  lcd.print(":");
  lcd.print(minute1);
  lcd.print(minute2);
  lcd.print(":");
  lcd.print(second1);
  lcd.print(second2);
}

byte setDate() {
  day = day1 * 10 + day2;
  month = month1 * 10 + month2;
  year = year1 * 1000 + year2 * 100 + year3 * 10 + year4;
  if (day == 0 && month == 0 && year == 0) {
    return 1;
  }
  month = month == 0 ? 1 : month;
  month = month > 12 ? 12 : month;
  day = day == 0 ? 1 : day;
  if ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && day > 31) {
    day = 31;
  } else if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
    day = 30;
  } else if ((month == 2 && ((year / 4 == 0 && year / 100 != 0) || year / 400 == 0)) && day > 29) {
    day = 29;
  } else if ((month == 2 && year / 4 != 0) && day > 28) {
    day = 28;
  }
  return 0;
}

byte setTime() {
  hour = hour1 * 10 + hour2;
  minute = minute1 * 10 + minute2;
  second = second1 * 10 + second2;
  if (hour == 0 && minute == 0 && second == 0) {
    return 1;
  }
  hour = hour > 23 ? 23 : hour;
  minute = minute > 59 ? 59 : minute;
  second = second > 59 ? 59 : second;
  return 0;
}

void reseetAllVariables() {
  day = 0;
  month = 0;
  year = 0;

  hour = 0;
  minute = 0;
  second = 0;

  day1 = 0;
  day2 = 0;

  month1 = 0;
  month2 = 0;

  year1 = 0;
  year2 = 0;
  year3 = 0;
  year4 = 0;

  hour1 = 0;
  hour2 = 0;

  minute1 = 0;
  minute2 = 0;

  second1 = 0;
  second2 = 0;

  dayOfWeek = 0;

  dateCursor = 0;
  timeCursor = 0;
}