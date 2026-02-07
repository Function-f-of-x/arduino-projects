

int hours = 0, mins = 0, secs = 0;

boolean isRepeat = false;

unsigned long t;

void setup() {
  Serial.begin(9600);
  delay(2000);
}

void loop() {
  String time;
  if (hours < 10) {
    time += 0;
  }
  time += hours;
  time += ":";
  if (mins < 10) {
    time += 0;
  }
  time += mins;
  time += ":";
  if (secs < 10) {
    time += 0;
  }
  time += secs;
  if (!isRepeat) {
    t = millis();
  }
  if (millis() - t == 1000) {
    secs++;
    t = millis();
    Serial.println(time);
  }
  if (secs == 60) {
    mins++;
    secs = 0;
  }
  if (mins == 60) {
    hours++;
    mins = 0;
  }
  isRepeat = true;
}
