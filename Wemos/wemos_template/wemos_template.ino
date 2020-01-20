#include <Wire.h>
#include <ESP8266WiFi.h>
#include <string.h>
#define PORT 3000 
#include <cstring>

// Network SSID
const char* ssid = "Wij gebruiken een IDE";
const char* password = "Mijnarends";

WiFiServer wifiServer(PORT);
IPAddress ip(10, 42, 0, 15);
IPAddress GW(10, 42, 0, 1);
IPAddress netmask(255, 255, 255, 0);

void initWiFi();
void connectWithClient();
void turnOnActuators();
void readDigitalSensors();
void readAnalogSensors();

int c = 0;
String h = "";

char buffer1[10] = {0};
char buffer2[20] = {0};

String stringbuffer0;
String stringbuffer1;
String stringbuffer2;

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

void readDigitalSensors()
{
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x00));      
  Wire.endTransmission();
  Wire.requestFrom(0x38, 1);   
  unsigned int inputs = Wire.read();  
  if (inputs % 2 == 0){
     inputs = 0;
  }
  else {
    inputs = 1;
  }
  //Serial.print("Digital in: ");
  //Serial.println(inputs&0x0F);
  //Serial.println(inputs);
  itoa(inputs, buffer1, 10);
}

void turnOnActuators()
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
  Serial.print("Waarde lampje: ");
  Serial.println(c - '0');
  Wire.endTransmission();
}

void readAnalogSensors()
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
  itoa(anin0, buffer2, 10);
}

void connectWithClient()
{
  WiFiClient client = wifiServer.available();
  
  if (client) {
 
    while (client.connected()) {
 
      while (client.available()>0) {
        c = client.read();
        Serial.print(c);
        turnOnLed();
      }
  
      readDigitalSensors();
      readAnalogSensors();

      String a = "2";
      String b = "3";
      String c = ";";
      stringbuffer1 = buffer1;
      stringbuffer2 = buffer2;
      stringbuffer0 = a + c + stringbuffer1 + c + b + c + stringbuffer2 + c;

      char writebuffer[50];
      strcpy(writebuffer, stringbuffer0.c_str());
      client.write(writebuffer);
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
  WiFi.mode(WIFI_STA);
  WiFi.config(ip, GW, netmask, GW);
 
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
