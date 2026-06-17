unsigned long t1;
unsigned long t2;


void setup() {
  pinMode(9, OUTPUT);

}

void loop() {
  if (millis() - t1 > 1000) {
    digitalWrite(9, HIGH);
    t1 = millis();
  }

  if (millis() - t2 > 1000) {
    digitalWrite(9, LOW);
    t2 = millis();
  }

}
