
int TrigPin = 8;
int EchoPin = 9;
int led5 = 5;
int led6 = 6;
int led7 = 7;
int timer_led = 2;
int position = 0;

void setup()
{
pinMode(TrigPin,OUTPUT);
pinMode(EchoPin,INPUT);
pinMode(led7, OUTPUT);
pinMode(timer_led, OUTPUT);
}
void loop()
{
int distance,duration;
digitalWrite(TrigPin,HIGH);
delayMicroseconds(11);
digitalWrite(TrigPin,LOW);
duration = pulseIn(EchoPin, HIGH);
if (duration<900) // Если расстояние менее 9 сантиметров
{
digitalWrite(timer_led, HIGH); // Светодиод горит
}
else
{
digitalWrite(timer_led, LOW); // иначе не горит
}
delay(100); //защита от дребезга
if (duration<900) position = position + 1;
if(position > 0 && (digitalRead(timer_led) == LOW && (digitalRead(led7) == LOW )))
digitalWrite(led7, HIGH),(position = 0);
delay(100); 
if (position > 6 )digitalWrite(led7, LOW),(position =0),delay(1000);
}
