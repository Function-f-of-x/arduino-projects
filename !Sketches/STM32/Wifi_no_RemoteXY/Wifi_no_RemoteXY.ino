#define LED_LOW HIGH
#define LED_HIGH LOW

HardwareSerial Serial2(PA3, PA2);

bool ledState = false;
unsigned long lastStatusSend = 0;
unsigned long lastPingReceived = 0;
bool espConnected = false;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LED_LOW);
  delay(500);

  Serial2.begin(115200);
  serialPOST("READY");
}

void loop() {
  if (Serial2.available()) {
    String msg = serialGET();

    if (msg == "ON") {
      ledState = true;
      digitalWrite(LED_BUILTIN, LED_HIGH);
      serialPOST("ON");
      espConnected = true;
      lastPingReceived = millis();
    } else if (msg == "OFF") {
      ledState = false;
      digitalWrite(LED_BUILTIN, LED_LOW);
      serialPOST("OFF");
      espConnected = true;
      lastPingReceived = millis();
    } else if (msg == "TOGGLE") {
      ledState = !ledState;
      digitalWrite(LED_BUILTIN, ledState ? LED_HIGH : LED_LOW);
      serialPOST(ledState ? "ON" : "OFF");
      espConnected = true;
      lastPingReceived = millis();
    } else if (msg == "PING") {
      serialPOST("PONG");
      espConnected = true;
      lastPingReceived = millis();
    }
  }

  if (millis() - lastStatusSend > 5000) {
    serialPOST(ledState ? "ON" : "OFF");
    lastStatusSend = millis();
  }

  if (millis() - lastPingReceived > 5000 && lastPingReceived > 0) {
    espConnected = false;
  }
}

void serialPOST(String msg) {
  Serial2.println("POST:" + msg);
}

String serialGET() {
  String msg = Serial2.readStringUntil('\n');
  if (msg.startsWith("GET:")) {
    return "";
  }
  msg.replace("POST:", "");
  msg.trim();
  Serial2.println("GET:" + msg);
  return msg;
}