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

// настройки соединения 
#define REMOTEXY_SERIAL Serial
#define REMOTEXY_SERIAL_SPEED 115200
#define REMOTEXY_WIFI_SSID "Arduino"
#define REMOTEXY_WIFI_PASSWORD "2wsx2wsx2wsx"
#define REMOTEXY_SERVER_PORT 6377


// конфигурация интерфейса  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =   // 94 bytes
  { 255,3,0,0,0,87,0,16,162,0,10,48,11,25,15,15,189,29,31,208,
  146,208,154,208,155,46,0,189,208,146,208,171,208,154,208,155,46,0,10,48,
  44,25,15,15,1,29,31,208,146,208,154,208,155,46,0,1,208,146,208,171,
  208,154,208,155,46,0,10,48,75,25,15,15,135,29,31,208,146,208,154,208,
  155,46,0,135,208,146,208,171,208,154,208,155,46,0 };
  
// структура определяет все переменные и события вашего интерфейса управления 
struct {

    // input variables
  uint8_t pushSwitch_1; // =1 если включено, иначе =0 
  uint8_t pushSwitch_2; // =1 если включено, иначе =0 
  uint8_t pushSwitch_3; // =1 если включено, иначе =0 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

#define PIN_PUSHSWITCH_1 10
#define PIN_PUSHSWITCH_2 11
#define PIN_PUSHSWITCH_3 12


void setup() 
{
  RemoteXY_Init (); 
  
  pinMode (PIN_PUSHSWITCH_1, OUTPUT);
  pinMode (PIN_PUSHSWITCH_2, OUTPUT);
  pinMode (PIN_PUSHSWITCH_3, OUTPUT);
  pinMode(13, OUTPUT); 
  digitalWrite(13, LOW);
  // TODO you setup code
  
}

void loop() 
{ 
  RemoteXY_Handler ();
  
  digitalWrite(PIN_PUSHSWITCH_1, (RemoteXY.pushSwitch_1==0)?LOW:HIGH);
  digitalWrite(PIN_PUSHSWITCH_2, (RemoteXY.pushSwitch_2==0)?LOW:HIGH);
  digitalWrite(PIN_PUSHSWITCH_3, (RemoteXY.pushSwitch_3==0)?LOW:HIGH);
  
  // TODO you loop code
  // используйте структуру RemoteXY для передачи данных
  // не используйте функцию delay() 


}