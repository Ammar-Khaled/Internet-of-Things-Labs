#include <WiFi.h>
#include <WebServer.h>
#include <WiFiClient.h>

IPAddress staticIP(192,168,1,10);
IPAddress subnetMask(255,255,255,0);
IPAddress gatewayIP(192,168,1,1);
WebServer server(80);

void getIndexPage() {
  server.send(200, "text/html", "<h1>Welcome to ESP web server!</h1>");
}


void setup() {
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");

  // set ESP WiFi mode to be Access Point and Station
  WiFi.mode(WIFI_AP_STA);

  /*
  connect ESP to virtual wokwi wifi network using:
  WiFi.begin(char[] network_ssd,char[] network_password)
  */
  WiFi.begin("Wokwi-GUEST", "");
  Serial.print("Connecting to WiFi");
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected!");

  /*
  set a static ip address for ESP using:
  WiFi.config(IPAddress local_ip, IPAddress gateway, IPAddress subnet)
  */
  WiFi.config(staticIP, gatewayIP, subnetMask);

  // print connection info
  Serial.println("ESP IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Subnet Mask: ");
  Serial.println(WiFi.subnetMask());
  Serial.println("Gateway IP: ");
  Serial.println(WiFi.gatewayIP());

  /*
  set ESP as a soft access point using:
  WiFi.softAP(char[] network_ssd, char[] password)
  password: min => 8char and max => 63char
  */
  WiFi.softAP("ESP_network","12345678");

  // print acess point IP
  Serial.print("ESP Access Point IP: ");
  Serial.println(WiFi.softAPIP());

  server.begin();
  server.on("/", getIndexPage);
}


void loop() {
  // print number of devices connected to ESP every five seconds
  delay(5000);
  Serial.print("number of devices connected to ESP: ");
  Serial.println(WiFi.softAPgetStationNum());

  server.handleClient();
}
