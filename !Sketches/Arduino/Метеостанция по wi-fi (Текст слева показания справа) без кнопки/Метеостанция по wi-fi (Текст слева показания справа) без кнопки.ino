//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

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
uint8_t RemoteXY_CONF[] =   // 37 bytes
  { 255,0,0,47,1,30,0,16,161,0,67,1,0,7,100,13,36,26,101,67,
  1,1,45,100,13,189,26,101,67,1,0,25,100,13,134,26,101 };
  
// структура определяет все переменные и события вашего интерфейса управления 
struct {

    // output variables
  char text_1[101];  // =строка UTF8 оканчивающаяся нулем 
  char text_3[101];  // =строка UTF8 оканчивающаяся нулем 
  char text_2[101];  // =строка UTF8 оканчивающаяся нулем 

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
          int Pres = (int)P;
          sprintf(RemoteXY.text_1, "Температура: %d°C", Temp);
          sprintf(RemoteXY.text_2, "Давление: %d мм", Pres);
          sprintf(RemoteXY.text_3, "Влажность: %d⁒", H);
        }
      }
    }
  }
}