#define LED_PIN PC13

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
  Serial.println("STM32 ready with ST-Link!");
}

void loop() {
  digitalWrite(LED_PIN, LOW);
  Serial.println("LED ON");
  delay(2000);
  digitalWrite(LED_PIN, HIGH);
  Serial.println("LED OFF");
  delay(2000);
}