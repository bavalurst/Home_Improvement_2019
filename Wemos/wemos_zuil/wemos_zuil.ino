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
void turnOnLedAndBuzzer();
void readSwitch();
void readSmokeDetector();

int c = 0;
unsigned int anin0 = 0;
unsigned int anin1 = 0;

char buffer1[20];
char buffer2[20];
String sensorString;
String EndOfNumber = ";";

struct Sensor {
  String key;
  String value; 
}Switch, Smoke;

struct Actuator {
  int key = 0;
  int value = 0;
}Led, Buzzer; // buzzer actuator = 1

void setup() {
  Wire.begin();
  Serial.begin(115200);
  delay(10);

  initWiFi();

  Switch.key = "12";
  Smoke.key = "13";
  Led.key = 11;
  Buzzer.key = 10;
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
  Serial.print("Digital in: ");
  Serial.println(inputs&0x0F);
  Serial.println(inputs);
  itoa(inputs, buffer1, 10);
}

void turnOnLedAndBuzzer()
{
  
  // Begin transmissie met leds
  Wire.beginTransmission(0x38);
  Wire.write(byte(0x03));
  Wire.write(byte(0x0F));
  Wire.endTransmission();

  // Zet led op basis van ontvangen state van de PI
  Wire.beginTransmission(0x38);
  Wire.write(byte(0x01));
  Wire.write(byte(1 << 4)); // zet led op basis van ontvangen state
  Wire.endTransmission();
}

void readSmokeDetector()
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
  Serial.print("analog in 0: ");
  Serial.println(anin0);   
  itoa(anin0, buffer2, 10);
}

void connectWithClient()
{
  WiFiClient client = wifiServer.available();
  
  if (client) {
      Serial.println("1");
    while (client.connected()) {
      Serial.println("2");
      while (client.available()>0) {
        Serial.println("3");
        c = client.read();
        
        if(c - '0' == 1)
        {
          if(c - '0' == 0)
          {
             c = client.read();
             Buzzer.value = c - '0'; 
          }else if(c - '0' == 1)
          {
            c = client.read();
            Led.value = c - '0'; 
          }
        }
        turnOnLedAndBuzzer();
      }
      readSwitch();
      readSmokeDetector();

      Switch.value = buffer1;
      Smoke.value = buffer2;
      sensorString = Switch.key + EndOfNumber + Switch.value + EndOfNumber + Smoke.key + EndOfNumber + Smoke.value + EndOfNumber;

      char writebuffer[50];
      strcpy(writebuffer, sensorString.c_str());
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
