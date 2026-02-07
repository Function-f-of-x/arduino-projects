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
uint8_t RemoteXY_CONF[] =   // 19 bytes
  { 255,0,0,12,0,12,0,16,162,0,67,1,241,19,131,22,8,27,12 };
  
// структура определяет все переменные и события вашего интерфейса управления 
struct {

    // output variables
  char text_1[101];  // =строка UTF8 оканчивающаяся нулем 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////



void setup()
{
  RemoteXY_Init (); 
  pinMode(9, OUTPUT);
  pinMode(6, INPUT);
  
  // TODO you setup code
  
}

void loop() 
{ 
  RemoteXY_Handler ();
  if (digitalRead(6) == 1) {
    digitalWrite(9, HIGH);
    sprintf(RemoteXY.text_1, "");    
  }    
  else {
    digitalWrite(9, LOW);
    sprintf(RemoteXY.text_1, "KTO TУT!?");        
  }
  // TODO you loop code
  // используйте структуру RemoteXY для передачи данных
  // не используйте функцию delay(
}

