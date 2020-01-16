#include <Wire.h>
#include <ESP8266WiFi.h>
#include <string.h>
#define PORT 3000 
#include <cstring>

// Network SSID
const char* ssid = "Wij gebruiken een IDE";
const char* password = "Mijnarends";

WiFiServer wifiServer(PORT);

void initWiFi();
void connectWithClient();
void turnOnFan();
void turnOnCooler();
void readSwitch();
void readTempSensors();

int c = 0;
unsigned int anin0 = 0;
unsigned int anin1 = 0;

char buffer1[20];
char buffer2[20];
char buffer3[20];
String sensorString;
String EndOfNumber = ";";

struct Sensor {
  String key;
  String value; 
}Switch, tempFridge, tempHeatsink;

struct Actuator {
  int key = 0;
  int value = 0;
}Fan, Cooler;

void setup() {
  Wire.begin();
  Serial.begin(115200);
  
  pinMode(D5, OUTPUT);  // Cooler
  
  delay(10);

  initWiFi();

  Switch.key = "21";
  tempFridge.key = "19";
  tempHeatsink.key = "20";
  Fan.key = 18;

  Fan.value = 1;
  Cooler.value = 1;
}
 
void loop() {
  connectWithClient();
}

void readSwitch()
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

void turnOnFan()
{ 
  // Begin transmissie met leds
  Wire.beginTransmission(0x38);
  Wire.write(byte(0x03));
  Wire.write(byte(0x0F));
  Wire.endTransmission();

  // Zet led op basis van ontvangen state van de PI
  Wire.beginTransmission(0x38);
  Wire.write(byte(0x01));
  Wire.write(byte(Fan.value << 4)); // zet led op basis van ontvangen state
  Wire.endTransmission();
}

void turnOnCooler()
{ 
  digitalWrite(D5, Cooler.value);     // Zet koelelement state op basis van ontvangen data 
}

void readTempSensors()
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

  unsigned int anin1 = Wire.read() & 0x03;    
  anin1 = anin1 << 8;                        
  anin1 = anin1 | Wire.read();
     
  itoa(anin1, buffer2, 10);
  itoa(anin0, buffer3, 10);
}

void connectWithClient()
{
  WiFiClient client = wifiServer.available();
  
  if (client) {
 
    while (client.connected()) {
 
      while (client.available()>0) {
        c = client.read();
        
        if(c - '0' == 1)
        {
          Serial.print("C : ");
          c = client.read();
          if(c - '0' == 8)
          {
            Serial.print("C : ");
            c = client.read();
            Fan.value = c - '0';
            Cooler.value = c - '0';
          }
        }
      }
      turnOnCooler();
      turnOnFan();
      readSwitch();
      readTempSensors();

      Switch.value = buffer1;
      tempFridge.value = buffer2;
      tempHeatsink.value = buffer3;
      sensorString = Switch.key + EndOfNumber + Switch.value + EndOfNumber + tempFridge.key + EndOfNumber + tempFridge.value + EndOfNumber;

      char writebuffer[50];
      strcpy(writebuffer, sensorString.c_str());
      client.write(writebuffer);
      delay(10);
    }
    client.stop();
    Serial.println(" ");
    Serial.println("Client disconnected");
    Serial.println(sensorString);
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
