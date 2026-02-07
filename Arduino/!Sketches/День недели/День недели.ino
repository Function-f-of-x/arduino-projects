byte day;
byte month;
short year;

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println("Введите день:");
  while (Serial.available() == 0) {
  }
  day = Serial.parseInt();
  Serial.println("Введите месяц:");
  while (Serial.available() == 0) {
  }
  month = Serial.parseInt();
  Serial.println("Введите год:");
  while (Serial.available() == 0) {
  }
  year = Serial.parseInt();
  char[] for_print;
  sprintf(for_print, "%2d.%2d.%4d %s", day, month, year, getDayOfWeek(dayOfWeek()));
  Serial.println(String(for_print));
}

String getDayOfWeek(byte day_of_week) {
  switch (day_of_week) {
    case 1:
      return "был понедельник";
    case 2:
      return "был вторник";
    case 3:
      return "была среда";
    case 4:
      return "был четверг";
    case 5:
      return "была пятница";
    case 6:
      return "была суббота";
    case 7:
      return "было воскресенье";
  }
}

byte dayOfWeek() {
  byte d = day;
  byte m = month - 1;
  short y = year;
  byte dow_codes[] = { 7, 1, 2, 3, 4, 5, 6 };
  byte month_codes[] = { 6, 2, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
  byte year_codes[] = { 0, 1, 2, 3, 5, 6, 0, 1, 3, 4, 5, 6, 1, 2, 3, 5, 0, 1, 2, 3, 5, 6, 0, 1, 3, 4, 5, 6, 1 };
  if (leapYear(y)) {
    month_codes[0] = 5;
    month_codes[1] = 1;
  }

  if (y < 2000) {
    while (y < 2000) {
      y += 28;
    }
  } else if (y > 2028) {
    while (y > 2028) {
      y -= 28;
    }
  }
  y -= 2000;

  dow = (d + month_codes[m - 1] + year_codes[y]) % 7;  
  return dow_codes[dow];
}

boolean leapYear(short y) {
  return ((y / 4 == 0 && y / 100 != 0) || y / 400 == 0);
}
