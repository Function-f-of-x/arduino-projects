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
uint8_t RemoteXY_CONF[] =   // 113 bytes
  { 255,1,0,13,0,106,0,16,162,0,65,96,33,2,32,32,67,1,56,32,
  34,17,24,162,11,129,0,7,38,37,6,24,208,160,208,176,209,129,209,129,
  209,130,208,190,209,143,208,189,208,184,208,181,58,0,2,0,56,49,34,12,
  135,26,31,31,208,146,208,154,208,155,0,208,146,208,171,208,154,208,155,0,
  129,0,4,52,42,6,24,208,161,208,184,208,179,208,189,208,176,208,187,208,
  184,208,183,208,176,209,134,208,184,209,143,58,0 };
  
// структура определяет все переменные и события вашего интерфейса управления 
struct {

    // input variables
  uint8_t switch_1; // =1 если переключатель включен и =0 если отключен 

    // output variables
  uint8_t led_1_r; // =0..255 яркость красного цвета индикатора 
  uint8_t led_1_g; // =0..255 яркость зеленого цвета индикатора 
  char text_1[11];  // =строка UTF8 оканчивающаяся нулем 

    // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)


/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////

#include <Ultrasonic.h>
#define buzzer 8

Ultrasonic ultrasonic(7, 11);
int distance;
int red;
int green;
unsigned long t;

void setup() {
  RemoteXY_Init ();
  
  pinMode(buzzer, OUTPUT);
}

void loop() {
  RemoteXY_Handler ();
  
  distance = ultrasonic.read();
  
  if (distance <= 70) { 
    int zaderzhka = distance * 10;
    if (millis() - t > zaderzhka) {
      t = millis();
      if (RemoteXY.switch_1 == 1) { 
        tone(buzzer, 2000, 150);
      }
    }
    if (distance < 10) {
      zaderzhka = 0;
      red = 240;
      green = 0;
    } else if (distance < 30) {
      red = 240;
      green = 12;
      int s = distance - 10;
      for (int i = 0; i < s; i++) {
        green += 12;
      }
    } else if (distance < 50) {
      red = (50 - distance) * 12;
      green = 240;
    } else if (distance <= 70) {
      red = 0;
      green = (70 - distance) * 12;
    }
    RemoteXY.led_1_r = red;
    RemoteXY.led_1_g = green;
  } else {
    RemoteXY.led_1_r = 0;
    RemoteXY.led_1_g = 0;
  }
  sprintf(RemoteXY.text_1, "%d см", distance);
  delay(25);
}

