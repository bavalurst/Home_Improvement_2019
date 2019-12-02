#include "ESP8266WiFi.h"

const char* ssid = "Wij gebruiken een IDE"; //Enter SSID
const char* password = "Mijnarends"; //Enter Password
const char* host ="10.42.0.1";
const uint16_t port = 3000;


WiFiServer wifiServer(3000);

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting..");
  }
 
  Serial.print("Connected to WiFi. IP:");
  Serial.println(WiFi.localIP());
 
  wifiServer.begin();
}

void loop() {
  WiFiClient client = wifiServer.available();
  if (client) {
    while (client.connected()) {
      while (client.available()>0) {
        char c = client.read();
        Serial.write(c);
      }
      delay(10);
      client.println("hello ack from server");
    }
    client.stop();
    Serial.println("Client disconnected");
  }
}