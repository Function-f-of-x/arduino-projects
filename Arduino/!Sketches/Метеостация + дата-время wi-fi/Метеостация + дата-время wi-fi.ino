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
uint8_t RemoteXY_CONF[] =   // 152 bytes
  { 255,0,0,74,0,145,0,17,0,0,0,161,2,106,200,200,80,1,1,5,
  0,67,83,5,21,24,23,0,177,21,2,24,26,31,129,7,60,73,30,5,
  21,190,10,24,208,162,208,181,208,188,208,191,208,181,209,128,208,176,209,130,
  209,131,209,128,208,176,32,32,32,32,32,32,208,148,208,176,208,178,208,187,
  208,181,208,189,208,184,208,181,32,32,32,32,32,32,208,146,208,187,208,176,
  208,182,208,189,208,190,209,129,209,130,209,140,0,67,6,120,21,25,239,40,
  103,21,1,36,26,11,67,238,103,74,65,55,40,95,21,1,135,26,21,67,
  238,103,74,65,118,40,101,21,1,204,26,11 };
  
// структура определяет все переменные и события вашего интерфейса управления 
struct {

    // output variables
  char dateTime[31]; // =строка UTF8 оканчивающаяся нулем
  char temp[11]; // =строка UTF8 оканчивающаяся нулем
  char pres[21]; // =строка UTF8 оканчивающаяся нулем
  char hum[11]; // =строка UTF8 оканчивающаяся нулем

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0

} RemoteXY;   
#pragma pack(pop)
 
/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

#include <DS1307.h>
#include <stDHT.h>
#include <SFE_BMP180.h>
#include <Wire.h>

DHT sens(DHT11);
SFE_BMP180 bmp180;
DS1307 clock;

void setup() {
  RemoteXY_Init();

  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);
  bmp180.begin();
  clock.begin();
  clock.startClock();
}

void loop() {
  RemoteXY_Handler();

  char status;
  double T, P;
  bool sucsess = false;
  int H = sens.readHumidity(7);
  status = bmp180.startTemperature();
  clock.getTime();

  if (status != 0) {
    RemoteXY_delay(500);
    status = bmp180.getTemperature(T);
    if (status != 0) {
      status = bmp180.startPressure(3);
      if (status != 0) {
        RemoteXY_delay(500);
        status = bmp180.getPressure(P, T);
        P *= 0.750064;
        P += 3.5;
        if (status != 0) {
          int Temp = (int)T;
          // int Temp = sens.readTemperature(7);
          int Pres = (int)P;
          sprintf(RemoteXY.dateTime, "%02d.%02d.%d  %02d:%02d:%02d", clock.dayOfMonth, clock.month, clock.year + 2000, clock.hour, clock.minute, clock.second);
          sprintf(RemoteXY.temp, "%d°C", Temp);
          sprintf(RemoteXY.pres, "%d мм", Pres);
          sprintf(RemoteXY.hum, "%d⁒", H);
        }
      }
    }
  }
}