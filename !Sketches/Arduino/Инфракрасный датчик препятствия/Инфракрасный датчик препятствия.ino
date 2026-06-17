void setup() {
  pinMode(9, OUTPUT);
  pinMode(6, INPUT);

}

void loop() {
  if (digitalRead(6) == 1)
    digitalWrite(9, HIGH);
  else
    digitalWrite(9, LOW);  

}
