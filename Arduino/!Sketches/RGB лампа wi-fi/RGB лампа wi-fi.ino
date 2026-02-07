//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// можете включить вывод отладочной информации в Serial на 115200
//#define REMOTEXY__DEBUGLOG

// определение режима соединения и подключение библиотеки RemoteXY
#define REMOTEXY_MODE__ESP8266_HARDSERIAL_POINT


// настройки соединения
#define REMOTEXY_SERIAL Serial
#define REMOTEXY_SERIAL_SPEED 115200
#define REMOTEXY_WIFI_SSID "Arduino"
#define REMOTEXY_WIFI_PASSWORD "2wsx2wsx2wsx"
#define REMOTEXY_SERVER_PORT 6377


#include <RemoteXY.h>

// конфигурация интерфейса RemoteXY
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =  // 31 bytes
  { 255, 0, 0, 3, 0, 24, 0, 17, 0, 0, 0, 8, 2, 106, 200, 200, 92, 1, 1, 1,
    0, 65, 24, 59, 43, 43, 253, 252, 204, 97, 119 };

// структура определяет все переменные и события вашего интерфейса управления
struct {

  // output variables
  uint8_t led_r;  // =0..255 яркость красного цвета индикатора
  uint8_t led_g;  // =0..255 яркость зеленого цвета индикатора
  uint8_t led_b;  // =0..255 яркость зеленого цвета индикатора

  // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

#include <IRremote.hpp>
#include "CODES_COLORS.h"

#define IR_RECEIVE_PIN 8

uint8_t resR, resG, resB;
String resMode = "color";

IRRawDataType data;

uint16_t speed = 500;

void setup() {
  RemoteXY_Init();
  IrReceiver.begin(IR_RECEIVE_PIN);
  setColor(0, 0, 0);
  reserv();
}

void loop() {
  RemoteXY_Handler();
  if (IrReceiver.decode()) {
    data = IrReceiver.decodedIRData.decodedRawData;
switchData:
    switch (data) {
      case ON:
        if (resMode.equals("color")) {
          setColor(resR, resG, resB);
        } else if (resMode.equals("flash")) {
          IrReceiver.resume();
          while (true) {
            setColor(255, 0, 0);
            RemoteXY_delay(speed);
            if (check(FLASH))
              goto switchData;
            setColor(0, 255, 0);
            RemoteXY_delay(speed);
            if (check(FLASH))
              goto switchData;
            setColor(255, 255, 0);
            RemoteXY_delay(speed);
            if (check(FLASH))
              goto switchData;
            setColor(0, 0, 255);
            RemoteXY_delay(speed);
            if (check(FLASH))
              goto switchData;
            setColor(255, 0, 255);
            RemoteXY_delay(speed);
            if (check(FLASH))
              goto switchData;
            setColor(0, 255, 255);
            RemoteXY_delay(speed);
            if (check(FLASH))
              goto switchData;
            setColor(255, 255, 255);
            RemoteXY_delay(speed);
            if (check(FLASH))
              goto switchData;
          }
        } else if (resMode.equals("strobe")) {
          IrReceiver.resume();
          while (true) {
            for (uint8_t w = 255; w > 65; w--) {
              setColor(w, w, w);
              RemoteXY_delay(speed / 100);
              if (check(STROBE))
                goto switchData;
            }
            for (uint8_t w = 64; w < 254; w++) {
              setColor(w, w, w);
              RemoteXY_delay(speed / 100);
              if (check(STROBE))
                goto switchData;
            }
          }
        } else if (resMode.equals("fade")) {
          IrReceiver.resume();
          while (true) {
          for (uint8_t g = 0; g < 255; g++) {
            setColor(255, g, 0);
            RemoteXY_delay(speed / 100);
            if (check(FADE))
              goto switchData;
          }
          for (uint8_t r = 255; r > 0; r--) {
            setColor(r, 255, 0);
            RemoteXY_delay(speed / 100);
            if (check(FADE))
              goto switchData;
          }
          for (uint8_t b = 0; b < 255; b++) {
            setColor(0, 255, b);
            RemoteXY_delay(speed / 100);
            if (check(FADE))
              goto switchData;
          }
          for (uint8_t g = 255; g > 0; g--) {
            setColor(0, g, 255);
            RemoteXY_delay(speed / 100);
            if (check(FADE))
              goto switchData;
          }
          for (uint8_t r = 0; r < 255; r++) {
            setColor(r, 0, 255);
            RemoteXY_delay(speed / 100);
            if (check(FADE))
              goto switchData;
          }
          for (uint8_t g = 0; g < 255; g++) {
            setColor(255, g, 255);
            RemoteXY_delay(speed / 100);
            if (check(FADE))
              goto switchData;
          }
          for (uint8_t gb = 255; gb > 0; gb--) {
            setColor(255, gb, gb);
            RemoteXY_delay(speed / 100);
            if (check(FADE))
              goto switchData;
          }
        }
        } else if (resMode.equals("smooth")) {
          IrReceiver.resume();
          while (true) {
            setColor(255, 0, 0);
            RemoteXY_delay(speed);
            if (check(SMOOTH))
              goto switchData;
            setColor(0, 255, 0);
            RemoteXY_delay(speed);
            if (check(SMOOTH))
              goto switchData;
            setColor(0, 0, 255);
            RemoteXY_delay(speed);
            if (check(SMOOTH))
              goto switchData;
          }
        }
        break;
      case OFF:
        setColor(0, 0, 0);
        break;
      case RED:
        resMode = "color";
        setColor(255, 0, 0);
        reserv();
        break;
      case ORANGE_RED:
        resMode = "color";
        setColor(255, 64, 0);
        reserv();
        break;
      case ORANGE:
        resMode = "color";
        setColor(255, 128, 0);
        reserv();
        break;
      case YELLOW:
        resMode = "color";
        setColor(255, 255, 0);
        reserv();
        break;
      case YELLOW_GREEN:
        resMode = "color";
        setColor(172, 255, 0);
        reserv();
        break;
      case GREEN:
        resMode = "color";
        setColor(0, 255, 0);
        reserv();
        break;
      case AQUAMARINE:
        resMode = "color";
        setColor(0, 255, 96);
        reserv();
        break;
      case AQUA:
        resMode = "color";
        setColor(0, 255, 128);
        reserv();
        break;
      case CYAN:
        resMode = "color";
        setColor(0, 255, 255);
        reserv();
        break;
      case LIGHT_BLUE:
        resMode = "color";
        setColor(0, 128, 255);
        reserv();
        break;
      case BLUE:
        resMode = "color";
        setColor(0, 0, 255);
        reserv();
        break;
      case VIOLET:
        resMode = "color";
        setColor(128, 0, 255);
        reserv();
        break;
      case PURPLE:
        resMode = "color";
        setColor(172, 0, 255);
        reserv();
        break;
      case PINK:
        resMode = "color";
        setColor(255, 0, 255);
        reserv();
        break;
      case PINK_RED:
        resMode = "color";
        setColor(255, 0, 128);
        reserv();
        break;
      case WHITE:
        resMode = "color";
        setColor(255, 255, 255);
        reserv();
        break;
      case FLASH:
        IrReceiver.resume();
        resMode = "flash";
        while (true) {
          setColor(255, 0, 0);
          RemoteXY_delay(speed);
          if (check(FLASH))
            goto switchData;
          setColor(0, 255, 0);
          RemoteXY_delay(speed);
          if (check(FLASH))
            goto switchData;
          setColor(255, 255, 0);
          RemoteXY_delay(speed);
          if (check(FLASH))
            goto switchData;
          setColor(0, 0, 255);
          RemoteXY_delay(speed);
          if (check(FLASH))
            goto switchData;
          setColor(255, 0, 255);
          RemoteXY_delay(speed);
          if (check(FLASH))
            goto switchData;
          setColor(0, 255, 255);
          RemoteXY_delay(speed);
          if (check(FLASH))
            goto switchData;
          setColor(255, 255, 255);
          RemoteXY_delay(speed);
          if (check(FLASH))
            goto switchData;
        }
        break;
      case STROBE:
        IrReceiver.resume();
        resMode = "strobe";
        while (true) {
          for (uint8_t w = 255; w > 33; w--) {
            setColor(w, w, w);
            RemoteXY_delay(speed / 100);
            if (check(FADE))
              goto switchData;
          }
          for (uint8_t w = 32; w < 254; w++) {
            setColor(w, w, w);
            RemoteXY_delay(speed / 100);
            if (check(FADE))
              goto switchData;
          }
        }
        break;
      case FADE:
        IrReceiver.resume();
        resMode = "fade";
        while (true) {
          for (uint8_t g = 0; g < 255; g++) {
            setColor(255, g, 0);
            RemoteXY_delay(speed / 100);
            if (check(FADE))
              goto switchData;
          }
          for (uint8_t r = 255; r > 0; r--) {
            setColor(r, 255, 0);
            RemoteXY_delay(speed / 100);
            if (check(FADE))
              goto switchData;
          }
          for (uint8_t b = 0; b < 255; b++) {
            setColor(0, 255, b);
            RemoteXY_delay(speed / 100);
            if (check(FADE))
              goto switchData;
          }
          for (uint8_t g = 255; g > 0; g--) {
            setColor(0, g, 255);
            RemoteXY_delay(speed / 100);
            if (check(FADE))
              goto switchData;
          }
          for (uint8_t r = 0; r < 255; r++) {
            setColor(r, 0, 255);
            RemoteXY_delay(speed / 100);
            if (check(FADE))
              goto switchData;
          }
          for (uint8_t g = 0; g < 255; g++) {
            setColor(255, g, 255);
            RemoteXY_delay(speed / 100);
            if (check(FADE))
              goto switchData;
          }
          for (uint8_t gb = 255; gb > 0; gb--) {
            setColor(255, gb, gb);
            RemoteXY_delay(speed / 100);
            if (check(FADE))
              goto switchData;
          }
        }
        break;
      case SMOOTH:
        IrReceiver.resume();
        resMode = "smooth";
        while (true) {
          setColor(255, 0, 0);
          RemoteXY_delay(speed);
          if (check(SMOOTH))
            goto switchData;
          setColor(0, 255, 0);
          RemoteXY_delay(speed);
          if (check(SMOOTH))
            goto switchData;
          setColor(0, 0, 255);
          RemoteXY_delay(speed);
          if (check(SMOOTH))
            goto switchData;
        }
        break;
    }
  }
  IrReceiver.resume();
}

void reserv() {
  resR = RemoteXY.led_r;
  resG = RemoteXY.led_g;
  resB = RemoteXY.led_b;
}

void setColor(uint8_t red, uint8_t green, uint8_t blue) {
  RemoteXY.led_r = red;
  RemoteXY.led_g = green;
  RemoteXY.led_b = blue;
}

bool check(IRRawDataType MODE) {
  if (IrReceiver.decode()) {
    IRRawDataType dt = IrReceiver.decodedIRData.decodedRawData;
    IrReceiver.resume();
    if (dt == BR_SP_MINUS && speed < 2000) {
      speed += 100;
      RemoteXY_delay(100);
    } else if (dt == BR_SP_PLUS && speed > 100) {
      speed -= 100;
      RemoteXY_delay(100);
    } else if (dt == BR_SP_MINUS && speed >= 2000) {
      return 0;
    } else if (dt == BR_SP_PLUS && speed <= 100) {
      return 0;
    } else if (dt != MODE && dt != HOLD) {
      data = IrReceiver.decodedIRData.decodedRawData;
      return 1;
    }
    IrReceiver.resume();
  }
  return 0;
}
