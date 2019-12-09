#include <Wire.h>
#include <ESP8266WiFi.h>
#include <string.h>
#define PORT 3000 

// Network SSID
const char* ssid = "Wij gebruiken een IDE";
const char* password = "Mijnarends";

WiFiServer wifiServer(PORT);

void initWiFi();
void connectWithClient();
void turnOnLed();
void rotaryEncoder();

int c;
String h = "";

char buffer0[4] = {0};

unsigned int anin0 = 0;
unsigned int anin1 = 0;

struct Data {
  int id = 1;
  int state;
};

void setup() {
  Wire.begin();
  Serial.begin(115200);
  delay(10);

  initWiFi();
}
 
void loop() {

  connectWithClient();
}

void turnOnLed()
{
  
  // Begin transmissie met leds
  Wire.beginTransmission(0x38);
  Wire.write(byte(0x03));
  Wire.write(byte(0x0F));
  Wire.endTransmission();

  // Zet led op basis van ontvangen state van de PI
  Wire.beginTransmission(0x38);
  Wire.write(byte(0x01));
  Wire.write(byte(c - '0' << 4)); // zet led op basis van ontvangen state
  Wire.endTransmission();
}

void rotaryEncoder()
{
   //Inside loop for debugging purpose (hot plugging wemos module into i/o board). 
  Wire.beginTransmission(0x36);
  Wire.write(byte(0xA2));          
  Wire.write(byte(0x03));  
  Wire.endTransmission(); 

  //Read analog 10bit inputs 0&1
  Wire.requestFrom(0x36, 4);   
  anin0 = Wire.read()&0x03;  
  anin0=anin0<<8;
  anin0 = anin0|Wire.read();  
  anin1 = Wire.read()&0x03;  
  anin1=anin1<<8;
  anin1 = anin1|Wire.read(); 
  Serial.print("analog in 0: ");
  Serial.println(anin0);   

  itoa(anin0, buffer0, 10);
}

void connectWithClient()
{
  WiFiClient client = wifiServer.available();
  
  if (client) {
 
    while (client.connected()) {
 
      while (client.available()>0) {
        c = client.read();
      }
      turnOnLed();
      rotaryEncoder();
      client.write(buffer0);
      delay(10);
    }
 
    client.stop();
    Serial.println(" ");
    Serial.println("Client disconnected");
  }
}

void initWiFi()
{
  // Connect WiFi
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.hostname("Wemos");
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Print the IP address
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  wifiServer.begin();
}
