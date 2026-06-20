HardwareSerial Serial2(PA3, PA2);

bool ledState = false;
unsigned long lastStatusSend = 0;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);

  Serial2.begin(115200);
  Serial2.println("STM:READY");
  while (!Serial.available()) {
    Serial2.println("STM:WAITING");
    delay(2000);
  }
}

void loop() {
  if (Serial2.available()) {
    String msg = Serial2.readStringUntil('\n');
    msg.trim();

    if (msg == "CMD:ON") {
      ledState = true;
      digitalWrite(LED_BUILTIN, HIGH);
      Serial2.println("LED:ON");
    } else if (msg == "CMD:OFF") {
      ledState = false;
      digitalWrite(LED_BUILTIN, LOW);
      Serial2.println("LED:OFF");
    } else if (msg == "CMD:TOGGLE") {
      ledState = !ledState;
      digitalWrite(LED_BUILTIN, ledState ? HIGH : LOW);
      Serial2.println(ledState ? "LED:ON" : "LED:OFF");
    }
  }

  if (millis() - lastStatusSend > 5000) {
    Serial2.println(ledState ? "LED:ON" : "LED:OFF");
    lastStatusSend = millis();
  }
}