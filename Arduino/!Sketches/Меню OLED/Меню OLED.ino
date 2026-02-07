#include <Arduino.h>
#include <DS1307.h>
#include <SFE_BMP180.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <stDHT.h>

#include <IRremote.hpp>

#include "CODES_BUTTONS.h"

#define DHT_PIN 7
#define IR_PIN 8

DS1307 clock;
DHT sens(DHT11);
SFE_BMP180 bmp180;
U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

enum BMPState { BMP_IDLE,
                BMP_TEMP_WAIT,
                BMP_PRESS_WAIT };
BMPState bmpState = BMP_IDLE;

unsigned long bmpTimer = 0;
double bmpTemp = NAN, bmpPres = NAN;
char bmpStatus;

byte tempSensor;
byte day1, day2, month1, month2, year1, year2, hour1, hour2, minute1, minute2, second1, second2;
short day, month, year, hour, minute, second;
byte dayOfWeek;
byte dateCursor, timeCursor;
byte screen = 0;
bool showSeconds = true;

// Переменные для настройки даты/времени
bool settingDateTime = false;
byte settingStep = 0;
byte inputCursor = 0;
unsigned long lastInputTime = 0;
const unsigned long INPUT_TIMEOUT = 2000;
const unsigned long CONFIRMATION_DELAY = 3000;
bool dateSet = false;
bool timeSet = false;

void setup() {
  pinMode(DHT_PIN, OUTPUT);
  digitalWrite(DHT_PIN, HIGH);
  u8g2_initialize();
  clock.begin();
  clock.startClock();
  bmp180.begin();
  IrReceiver.begin(IR_PIN);
  // Serial.begin(9600);  // УДАЛЕНО
}

void loop() {
  Wire.begin();
  clock.getTime();
  switch (screen) {
    case 0:
      drawWeather();
      break;
    case 1:
      if (!settingDateTime) {
        drawTime();
      } else {
        handleDateTimeSetting();
      }
      break;
  }

  long code = IR_decode();
  if (code) {
    // Serial.println(code, HEX);  // УДАЛЕНО
    if (!settingDateTime) {
      switch (code) {
        case BUTTON_UP:
          if (screen > 0) screen--;
          break;
        case BUTTON_DOWN:
          if (screen < 1) screen++;
          break;
        case BUTTON_OK:
          if (screen == 1) {
            settingDateTime = true;
            settingStep = 0;
            inputCursor = 0;
            dateSet = false;
            timeSet = false;
            lastInputTime = millis();
          }
          break;
        case BUTTON_LEFT:
        case BUTTON_RIGHT:
          showSeconds = !showSeconds;
          break;
      }
    } else {
      handleDateTimeInput(code);
    }
  }
}

void u8g2_initialize(void) {
  u8g2.begin();
  u8g2.enableUTF8Print();
  u8g2.setFont(u8g2_font_6x12_t_cyrillic);
  u8g2.setDrawColor(1);
  u8g2.setFontDirection(0);
}

long IR_decode() {
  if (IrReceiver.decode()) {
    long code = IrReceiver.decodedIRData.decodedRawData;
    IrReceiver.resume();
    return code;
  }
  return 0;
}

// ЗАМЕНА: String → const char*
const char* getDayOfWeek() {
  switch (clock.dayOfWeek) {
    case MON:
      return "Пн";
    case TUE:
      return "Вт";
    case WED:
      return "Ср";
    case THU:
      return "Чт";
    case FRI:
      return "Пт";
    case SAT:
      return "Сб";
    case SUN:
      return "Вс";
    default:
      return "?";
  }
}

void setDateNVariable(byte input) {
  switch (dateCursor) {
    case 0:
      day1 = input;
      break;
    case 1:
      day2 = input;
      break;
    case 2:
      month1 = input;
      break;
    case 3:
      month2 = input;
      break;
    case 4:
      year1 = input;
      break;
    case 5:
      year2 = input;
      break;
  }
}

void setTimeNVariable(byte input) {
  switch (timeCursor) {
    case 0:
      hour1 = input;
      break;
    case 1:
      hour2 = input;
      break;
    case 2:
      minute1 = input;
      break;
    case 3:
      minute2 = input;
      break;
    case 4:
      second1 = input;
      break;
    case 5:
      second2 = input;
      break;
  }
}

int getTempDHT11() {
  return sens.readTemperature(DHT_PIN);
}

int getHum() {
  return sens.readHumidity(DHT_PIN);
}

void updateBMP180() {
  switch (bmpState) {
    case BMP_IDLE:
      bmpStatus = bmp180.startTemperature();
      if (bmpStatus != 0) {
        bmpTimer = millis();
        bmpState = BMP_TEMP_WAIT;
      }
      break;
    case BMP_TEMP_WAIT:
      if (millis() - bmpTimer >= 5) {
        if (bmp180.getTemperature(bmpTemp)) {
          bmpStatus = bmp180.startPressure(3);
          if (bmpStatus != 0) {
            bmpTimer = millis();
            bmpState = BMP_PRESS_WAIT;
          } else {
            bmpState = BMP_IDLE;
          }
        } else {
          bmpState = BMP_IDLE;
        }
      }
      break;
    case BMP_PRESS_WAIT:
      if (millis() - bmpTimer >= 26) {
        if (bmp180.getPressure(bmpPres, bmpTemp)) {
          bmpPres *= 0.750064;  // Перевод в мм рт.ст.
        }
        bmpState = BMP_IDLE;
      }
      break;
  }
}

void drawWeather() {
  updateBMP180();

  double temperature = (tempSensor == 0) ? getTempDHT11() : bmpTemp;
  double pressure = bmpPres;
  double humidity = getHum();

  u8g2.firstPage();
  do {
    u8g2.setCursor(0, 12);
    u8g2.print(F("Температура: "));
    if (isnan(temperature))
      u8g2.print(F("-- C"));
    else {
      u8g2.print(temperature, tempSensor);
      u8g2.print(F(" C"));
    }

    u8g2.setCursor(0, 28);
    u8g2.print(F("Давление: "));
    if (isnan(pressure))
      u8g2.print(F("-- мм рс"));
    else {
      u8g2.print(pressure, 0);
      u8g2.print(F(" мм рс"));
    }

    u8g2.setCursor(0, 44);
    u8g2.print(F("Влажность: "));
    if (isnan(humidity))
      u8g2.print(F("--%"));
    else {
      u8g2.print(humidity, 0);
      u8g2.print(F("%"));
    }
  } while (u8g2.nextPage());
}

void drawTime() {
  char date[16];
  sprintf(date, "%02d.%02d.%d", clock.dayOfMonth, clock.month, clock.year + 2000);
  char time[11];
  sprintf(time, "%02d:%02d:%02d", clock.hour, clock.minute, clock.second);

  u8g2.firstPage();
  do {
    u8g2.setCursor(0, 14);
    u8g2.print(F("Дата: "));
    u8g2.print(getDayOfWeek());
    u8g2.print(F(", "));
    u8g2.print(date);

    u8g2.setCursor(0, 30);
    u8g2.print(F("Время: "));
    if (showSeconds) {
      u8g2.print(time);
    } else {
      for (int i = 0; i < 5; i++) {
        u8g2.print(time[i]);
      }
    }
  } while (u8g2.nextPage());
}

// --- Настройка даты/времени ---

void handleDateTimeSetting() {
  if (millis() - lastInputTime > INPUT_TIMEOUT && inputCursor > 0) {
    if ((settingStep == 0 && dateSet) || (settingStep == 1 && timeSet)) {
      settingStep++;
      inputCursor = 0;
      lastInputTime = millis();
    } else if (settingStep == 0 && !dateSet) {
      inputCursor = 0;
    } else if (settingStep == 1 && !timeSet) {
      inputCursor = 0;
    }
  }

  switch (settingStep) {
    case 0:
      displayDateTimeInput(F("Дата"), "ДД.ММ.20ГГ");
      break;
    case 1:
      displayDateTimeInput(F("Время"), "ЧЧ.ММ.СС");
      break;
    case 2:
      displayConfirmation();
      break;
  }
}

void handleDateTimeInput(long code) {
  if (code >= BUTTON_0 && code <= BUTTON_9) {
    byte digit = code - BUTTON_0;

    if (settingStep == 0) {
      if (inputCursor < 6) {
        setDateNVariableForSetting(digit);
        inputCursor++;
        lastInputTime = millis();
      }
      if (inputCursor == 6) {
        finalizeDateInput();
        dateSet = true;
        settingStep = 1;
        inputCursor = 0;
        lastInputTime = millis();
      }
    } else if (settingStep == 1) {
      if (inputCursor < 6) {
        setTimeNVariableForSetting(digit);
        inputCursor++;
        lastInputTime = millis();
      }
      if (inputCursor == 6) {
        finalizeTimeInput();
        timeSet = true;
        settingStep = 2;
        inputCursor = 0;
        lastInputTime = millis();
      }
    }
  }
}

void setDateNVariableForSetting(byte input) {
  switch (inputCursor) {
    case 0:
      day1 = input;
      break;
    case 1:
      day2 = input;
      break;
    case 2:
      month1 = input;
      break;
    case 3:
      month2 = input;
      break;
    case 4:
      year1 = input;
      break;
    case 5:
      year2 = input;
      break;
  }
}

void setTimeNVariableForSetting(byte input) {
  switch (inputCursor) {
    case 0:
      hour1 = input;
      break;
    case 1:
      hour2 = input;
      break;
    case 2:
      minute1 = input;
      break;
    case 3:
      minute2 = input;
      break;
    case 4:
      second1 = input;
      break;
    case 5:
      second2 = input;
      break;
  }
}

void finalizeDateInput() {
  day = day1 * 10 + day2;
  month = month1 * 10 + month2;
  year = 2000 + (year1 * 10 + year2);

  month = month == 0 ? 1 : (month > 12 ? 12 : month);
  day = day == 0 ? 1 : day;

  if ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && day > 31) {
    day = 31;
  } else if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
    day = 30;
  } else if ((month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)) && day > 29) {
    day = 29;
  } else if (month == 2 && day > 28) {
    day = 28;
  }

  byte shift[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
  int y = year;
  if (month < 3) y--;
  dayOfWeek = ((y + y / 4 - y / 100 + y / 400 + shift[month - 1] + day) % 7) + 1;
}

void finalizeTimeInput() {
  hour = hour1 * 10 + hour2;
  minute = minute1 * 10 + minute2;
  second = second1 * 10 + second2;

  hour = hour > 23 ? 23 : hour;
  minute = minute > 59 ? 59 : minute;
  second = second > 59 ? 59 : second;
}

void displayDateTimeInput(const __FlashStringHelper* title, const char* format) {
  u8g2.firstPage();
  do {
    int title_width = u8g2.getStrWidth(reinterpret_cast<const char*>(title));
    int format_width = u8g2.getStrWidth(format);
    int max_width = (title_width > format_width) ? title_width : format_width;
    int x_pos = (128 - max_width) / 2;

    u8g2.setCursor(x_pos, 20);
    u8g2.print(title);

    char input_str[16];
    if (settingStep == 0) {
      snprintf(input_str, sizeof(input_str), "%02d.%02d.%04d", day1 * 10 + day2, month1 * 10 + month2, 2000 + year1 * 10 + year2);
    } else {
      snprintf(input_str, sizeof(input_str), "%02d:%02d:%02d", hour1 * 10 + hour2, minute1 * 10 + minute2, second1 * 10 + second2);
    }

    for (int i = inputCursor; i < (int)strlen(input_str); i++) {
      if (input_str[i] != '.' && input_str[i] != ':') {
        input_str[i] = 'X';
      }
    }

    u8g2.setCursor(x_pos, 40);
    u8g2.print(input_str);
  } while (u8g2.nextPage());
}

void displayConfirmation() {
  clock.fillByYMD(year, month, day);
  clock.fillByHMS(hour, minute, second);
  clock.fillDayOfWeek(dayOfWeek);
  clock.setTime();

  u8g2.firstPage();
  do {
    u8g2.setCursor(10, 20);
    u8g2.print(F("Установлена дата:"));
    char date_str[16];
    sprintf(date_str, "%s, %02d.%02d.%d", getDayOfWeek(), day, month, year);
    u8g2.setCursor((128 - u8g2.getStrWidth(date_str)) / 2, 35);
    u8g2.print(date_str);

    char time_str[11];
    sprintf(time_str, "%02d:%02d:%02d", hour, minute, second);
    u8g2.setCursor((128 - u8g2.getStrWidth(time_str)) / 2, 50);
    u8g2.print(time_str);
  } while (u8g2.nextPage());

  delay(CONFIRMATION_DELAY);
  settingDateTime = false;
  screen = 1;
}