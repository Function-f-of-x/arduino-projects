byte s = 1;

void setup() {
  pinMode(6, INPUT);
  pinMode(9, OUTPUT);
}

void loop() {
  if (s == 1) {
    if (digitalRead(6) == 1) {
      delay(100);
      digitalWrite(9, HIGH);
      while (digitalRead(6) == 1) { 
        s = 1;
      }        
      s = 2;
    }
  }
  if (s == 2) {
    if (digitalRead(6) == 1) {
      delay(100);
      digitalWrite(9, LOW);
      while (digitalRead(6) == 1) {
        s = 2;
      }      
      s = 1;
    }
  }
}
