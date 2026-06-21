#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>

const char* ssid = "K2005";
const char* password = "2wsx2wsx2wsx";

ESP8266WebServer server(80);
bool ledState = false;
bool stmConnected = false;
unsigned long lastSyncAttempt = 0;
unsigned long lastPingSent = 0;
bool waitingForPong = false;

const char indexHtml[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="ru">

<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>STM32 LED</title>
  <style>
    * {
      margin: 0;
      padding: 0;
      box-sizing: border-box;
    }

    body {
      font-family: 'Segoe UI', Tahoma, sans-serif;
      background: #0f172a;
      color: #eee;
      display: flex;
      justify-content: center;
      align-items: center;
      min-height: 100vh;
    }

    .container {
      text-align: center;
      background: #1e293b;
      padding: 40px;
      box-shadow: 6px 6px #00000080;
    }

    .btn-shadow {
      box-shadow: 6px 6px #00000080;
      border-radius: 50%;
    }

    #led-btn {
      width: 200px;
      height: 200px;
      border-radius: 50%;
      border: none;
      font-size: 24px;
      font-weight: bold;
      cursor: pointer;
      transition: all 0.2s ease;
      background: #ff0000;
      color: white;
    }

    #led-btn.on {
      background: #00ff00;
    }

    #led-btn:active {
      transform: translate(4px, 4px);
    }

    #status {
      position: absolute;
      bottom: 3px;
      right: 8px;
      font-size: 18px;
      color: #2e405c;
      text-align: right;
    }
  </style>
</head>

<body>
  <div class="container">
    <div class="btn-shadow">
      <button id="led-btn" onclick="toggleLED()">OFF</button>
    </div>
  </div>
  <p id="status">Загрузка...</p>
  <script>
    let isLedOn = false;
    let status = document.getElementById('status');
    async function toggleLED() {
      isLedOn = !isLedOn;
      const btn = document.getElementById('led-btn');
      btn.textContent = isLedOn ? 'ON' : 'OFF';
      btn.classList.toggle('on', isLedOn);
      status.textContent = 'Отправка команды...';
      try {
        const response = await fetch('/toggle?state=' + (isLedOn ? '1' : '0'));
        const data = await response.json();
        status.textContent = data.message;
      } catch (e) {
        status.textContent = 'Ошибка связи!';
        isLedOn = !isLedOn;
        btn.textContent = isLedOn ? 'ON' : 'OFF';
        btn.classList.toggle('on', isLedOn);
      }
    }
    async function getStatus() {
      try {
        const response = await fetch('/status');
        const data = await response.json();
        isLedOn = data.state === 1;
        const btn = document.getElementById('led-btn');
        btn.textContent = isLedOn ? 'ON' : 'OFF';
        btn.classList.toggle('on', isLedOn);
        status.textContent = 'Подключено';
      } catch (e) {
        status.textContent = 'Нет связи с ESP';
      }
    }
    getStatus();
    setInterval(getStatus, 2000);
  </script>
</body>

</html>
)rawliteral";

void setup() {
  Serial.begin(115200);
  delay(1000);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    serialPOST("CONNECTING");
    if (Serial.available()) {
      serialGET();
    }
    delay(500);
  }
  serialPOST("READY:" + WiFi.localIP().toString());

  server.on("/", handleRoot);
  server.on("/toggle", handleToggle);
  server.on("/status", handleStatus);
  server.begin();
}

void loop() {
  server.handleClient();

  if (Serial.available()) {
    String msg = serialGET();
    if (msg == "ON") {
      ledState = true;
      stmConnected = true;
    } else if (msg == "OFF") {
      ledState = false;
      stmConnected = true;
    } else if (msg == "PONG") {
      waitingForPong = false;
      stmConnected = true;
    }
  }

  if (millis() - lastSyncAttempt > 1000) {
    lastSyncAttempt = millis();
    if (!waitingForPong) {
      serialPOST("PING");
      waitingForPong = true;
      lastPingSent = millis();
    } else if (millis() - lastPingSent > 3000) {
      stmConnected = false;
      waitingForPong = false;
    }
  }
}

void serialPOST(String msg) {
  Serial.println("POST:" + msg);
}

String serialGET() {
  String msg = Serial.readStringUntil('\n');
  if (msg.startsWith("GET:")) {
    return "";
  }
  msg.replace("POST:", "");
  msg.trim();
  Serial.println("GET:" + msg);
  return msg;
}

void handleRoot() {
  server.send_P(200, "text/html", indexHtml);
}

void handleToggle() {
  String state = server.arg("state");
  ledState = (state == "1");
  if (ledState) {
    serialPOST("ON");
  } else {
    serialPOST("OFF");
  }
  String json = "{\"state\":" + String(ledState ? 1 : 0) + ",\"message\":\"Отправлено\"}";
  server.send(200, "application/json", json);
}

void handleStatus() {
  String json = "{\"state\":" + String(ledState ? 1 : 0) + ",\"stmConnected\":" + String(stmConnected ? "true" : "false") + "}";
  server.send(200, "application/json", json);
}