#include <DS1307.h>

DS1307 clock;



void setup() {
  Serial.begin(9600);
  clock.begin();
  clock.startClock();
  pinMode(3, INPUT);
}

void loop() {
  while (digitalRead(3) == HIGH) {}
  clock.getTime();
  Serial.print("0 ");
  printDT();
  while (digitalRead(3) == LOW) {}
  clock.getTime();
  Serial.print("1 ");
  printDT();
}

void printDT() {
  char DT[21];
  sprintf(DT, "%02d.%02d.%d  %02d:%02d:%02d", clock.dayOfMonth, clock.month, clock.year + 2000, clock.hour, clock.minute, clock.second);
  Serial.println(DT);
}
