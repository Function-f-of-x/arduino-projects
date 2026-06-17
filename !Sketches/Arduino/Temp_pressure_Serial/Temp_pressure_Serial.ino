#include <Wire.h>
#include <SFE_BMP180.h>

SFE_BMP180 bmp180;

void setup() {
  Serial.begin(9600);

  bool sucsess = bmp180.begin();

  if (sucsess) {
    Serial.println("Vse normalno");
  }
}

void loop() {
  char status;
  double T, P;
  bool sucsess = false;

  status = bmp180.startTemperature();

  if (status != 0) {
    delay(1000);
    status = bmp180.getTemperature(T);

    if (status != 0) {
      status = bmp180.startPressure(3);

      if (status != 0) {
        delay(status + 5);
        status = bmp180.getPressure(P, T);
        P *= 0.750064;
        P += 3.5;

        if (status != 0) {
          Serial.print("Temperatura: ");
          Serial.print(T);
          Serial.println("℃");

          Serial.print("Davlenie: ");
          Serial.print(P);
          Serial.println(" mm rt. st.");
        }
      }
    }
  }
}
