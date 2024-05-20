#include <WiFi.h>
#include <ThingSpeak.h>
int trig = 25, echo = 26;
long t;
int distance;
WiFiClient client;
const long channelId = 2525071;
const char channelWriteApiKey[] = "8ZXJYZO9VVDUOXSK";
void setup() {
  // setup code here runs once:
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  WiFi.mode(WIFI_STA);
  WiFi.begin("Wokwi-GUEST", "");
  while(WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(500);
    ThingSpeak.begin(client);
  }
  Serial.println("\nConnected");
}

void loop() {
  // main code here runs repeatedly:
  digitalWrite(trig, LOW);  //clear
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  t = pulseIn(echo, HIGH);
  distance = .034 * (t / 2);
  Serial.println(distance);
  ThingSpeak.setField(1, distance);
  int ret = ThingSpeak.writeFields(channelId, channelWriteApiKey);
  if (ret == 200) {
    Serial.println("Data was uploaded");
  } else {
    Serial.println("Error!");
  }
}
