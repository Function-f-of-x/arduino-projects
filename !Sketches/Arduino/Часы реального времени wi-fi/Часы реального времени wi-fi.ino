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
uint8_t RemoteXY_CONF[] =   // 40 bytes
  { 255,0,0,31,0,33,0,17,0,0,0,161,3,106,200,200,84,200,200,1,
  1,1,0,67,255,80,107,16,9,29,185,22,10,79,183,32,1,24,26,31 };
  
// структура определяет все переменные и события вашего интерфейса управления 
struct {

    // output variables
  char dateTime[31]; // =строка UTF8 оканчивающаяся нулем

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0

} RemoteXY;   
#pragma pack(pop)
 
/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

#include <DS1307.h>
#include <Wire.h>

DS1307 clock;

void setup() {
  RemoteXY_Init();
  clock.begin();
  clock.startClock();
}

void loop() {
  RemoteXY_Handler();
  clock.getTime();
  sprintf(RemoteXY.dateTime, "%02d.%02d.%d  %02d:%02d:%02d", clock.dayOfMonth, clock.month, clock.year + 2000, clock.hour, clock.minute, clock.second);
}