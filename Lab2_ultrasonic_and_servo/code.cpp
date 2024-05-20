#include <Servo.h>
int ServoPin = 10, TriggerPin = 6, EchoPin = 7;
int duration, distance, angle;

Servo servo;
void setup() {
  pinMode(TriggerPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  Serial.begin(9600);
  servo.attach(ServoPin);
}

void loop() {
  digitalWrite(TriggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(TriggerPin, LOW);
  duration = pulseIn(EchoPin, HIGH);
  distance = duration * 0.034 / 2;
  Serial.println(distance);
  angle = map(distance, 30, 300, 0, 180);
  servo.write(angle);
  delay(50);
}
