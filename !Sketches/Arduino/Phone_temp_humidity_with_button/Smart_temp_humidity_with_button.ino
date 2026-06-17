/*
   -- New project --
   
   This source code of graphical user interface 
   has been generated automatically by RemoteXY editor.
   To compile this code using RemoteXY library 3.1.8 or later version 
   download by link http://remotexy.com/en/library/
   To connect using RemoteXY mobile app by link http://remotexy.com/en/download/                   
     - for ANDROID 4.11.1 or later version;
     - for iOS 1.9.1 or later version;
    
   This source code is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.    
*/

//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// определение режима соединения и подключение библиотеки RemoteXY 
#define REMOTEXY_MODE__ESP8266_HARDSERIAL_POINT

#include <RemoteXY.h>
#include <stDHT.h>
DHT sens (DHT11);

// настройки соединения
#define REMOTEXY_SERIAL Serial
#define REMOTEXY_SERIAL_SPEED 115200
#define REMOTEXY_WIFI_SSID "Arduino"
#define REMOTEXY_WIFI_PASSWORD "2wsx2wsx2wsx"
#define REMOTEXY_SERVER_PORT 6377


// конфигурация интерфейса  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =   // 95 bytes
  { 255,1,0,22,0,88,0,16,162,0,67,6,12,12,50,13,2,26,11,67,
  6,12,42,50,13,2,26,11,129,0,12,5,26,4,24,208,162,208,181,208,
  188,208,191,208,181,209,128,208,176,209,130,209,131,209,128,208,176,58,0,129,
  0,13,35,23,4,24,208,146,208,187,208,176,208,182,208,189,208,190,209,129,
  209,130,209,140,58,0,1,0,74,26,12,12,1,31,0 };
  
// структура определяет все переменные и события вашего интерфейса управления 
struct {

    // input variables
  uint8_t button_1; // =1 если кнопка нажата, иначе =0 

    // output variables
  char text_1[11];  // =строка UTF8 оканчивающаяся нулем 
  char text_2[11];  // =строка UTF8 оканчивающаяся нулем 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

#define PIN_BUTTON_1 7


void setup() 
{
  RemoteXY_Init (); 
  
  pinMode (PIN_BUTTON_1, OUTPUT);

}

void loop() 
{ 
  RemoteXY_Handler ();
  
  digitalWrite(PIN_BUTTON_1, (RemoteXY.button_1==0)?LOW:HIGH);
  if (RemoteXY.button_1 == 1) {
    int temp = sens.readTemperature(PIN_BUTTON_1);
    int hum = sens.readHumidity(PIN_BUTTON_1);

    sprintf(RemoteXY.text_1, "%d℃", temp);
    sprintf(RemoteXY.text_2, "%d⁒", hum);
  }
}
