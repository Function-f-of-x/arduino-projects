//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// можете включить вывод отладочной информации в Serial на 115200
// #define REMOTEXY__DEBUGLOG

// определение режима соединения и подключение библиотеки RemoteXY 
#define REMOTEXY_MODE__ESP8266_HARDSERIAL_POINT

#include <RemoteXY.h>

// настройки соединения 
#define REMOTEXY_SERIAL Serial
#define REMOTEXY_SERIAL_SPEED 115200
#define REMOTEXY_WIFI_SSID "Arduino"
#define REMOTEXY_WIFI_PASSWORD "2wsx2wsx2wsx"
#define REMOTEXY_SERVER_PORT 6377


// конфигурация интерфейса  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =   // 140 bytes
  { 255,0,0,53,0,133,0,16,161,0,129,0,242,13,121,5,24,208,162,208,
  181,208,188,208,191,208,181,209,128,208,176,209,130,209,131,209,128,208,176,32,
  32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,208,148,208,
  176,208,178,208,187,208,181,208,189,208,184,208,181,32,32,32,32,32,32,32,
  32,32,32,32,32,32,32,32,32,32,32,32,32,32,208,146,208,187,208,176,
  208,182,208,189,208,190,209,129,209,130,209,140,0,67,1,247,26,21,9,36,
  26,11,67,1,39,27,21,9,134,26,31,67,1,89,27,21,9,189,26,11 };
  
// структура определяет все переменные и события вашего интерфейса управления 
struct {

    // output variables
  char text_1[11];  // =строка UTF8 оканчивающаяся нулем 
  char text_2[31];  // =строка UTF8 оканчивающаяся нулем 
  char text_3[11];  // =строка UTF8 оканчивающаяся нулем 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////


#include <stDHT.h>
#include <SFE_BMP180.h>
#include <Wire.h>

DHT sens(DHT11);
SFE_BMP180 bmp180;

void setup() {
  RemoteXY_Init();
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);
  bmp180.begin();
}

void loop() {
  RemoteXY_Handler();
  char status;
  double T, P;
  bool sucsess = false;
  int H = sens.readHumidity(7);

  status = bmp180.startTemperature();

  if (status != 0) {
    RemoteXY_delay(1000);
    status = bmp180.getTemperature(T);

    if (status != 0) {
      status = bmp180.startPressure(3);

      if (status != 0) {
        RemoteXY_delay(status);
        status = bmp180.getPressure(P, T);
        P *= 0.750064;
        P += 3.5;
        if (status != 0) {
          int Temp = (int)T;
          // int Temp = sens.readTemperature(7);
          int Pres = (int)P;
          sprintf(RemoteXY.text_1, "%d°C", Temp);
          sprintf(RemoteXY.text_2, "%d мм", Pres);
          sprintf(RemoteXY.text_3, "%d⁒", H);
        }
      }
    }
  }
}