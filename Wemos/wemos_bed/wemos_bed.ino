#include <Wire.h>
#include <ESP8266WiFi.h>
#include <string.h>
#define PORT 3000 
#include <cstring>

// network SSID and wachtwoord
const char* ssid = "Groep 9";
const char* password = "LekkerBelangrijk";

WiFiServer wifiServer(PORT);

// statische IP
IPAddress ip(10, 42, 0, 10);
IPAddress GW(10, 42, 0, 1);
IPAddress netmask(255, 255, 255, 0);

void initWiFi();
void connectWithClient();
void turnOnLed();
void readSwitch();
void readRotaryEncoder();

char c;

unsigned int anin0 = 0;
unsigned int anin1 = 0;

char buffer1[20];
char buffer2[20];
String sensorString;
String EndOfNumber = ";";

struct Sensor {
  String key;
  String value; 
}Switch, RotaryEncoder;

void setup() {
  Wire.begin();
  Serial.begin(115200);
  delay(10);

  initWiFi();

  Switch.key = "2";
  RotaryEncoder.key = "3";

  c = 0;
}

// primaire loop
void loop() {
  connectWithClient();
}

// Deze functie leest de switch op het bed uit
void readSwitch()
{
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x00));      
  Wire.endTransmission();
  Wire.requestFrom(0x38, 1);   
  unsigned int inputs = Wire.read();   // hier wordt de switch uitgelezen
  if (inputs % 2 == 0){  // controleer of de switch is ingedrukt
     inputs = 0;
  }
  else {
    inputs = 1;
  }

  itoa(inputs, buffer1, 10);          // zet de integer waarde van de switch om naar een string, zodat deze over de socket verbinding gestuurd kan worden
}

// deze functie zet de led op het bed aan
void turnOnLed()
{
  // begin transmissie met leds
  Wire.beginTransmission(0x38);
  Wire.write(byte(0x03));
  Wire.write(byte(0x0F));
  Wire.endTransmission();

  // zet led op basis van ontvangen value van de PI
  Wire.beginTransmission(0x38);
  Wire.write(byte(0x01));
  Wire.write(byte(c - '0' << 4)); // zet led op basis van ontvangen value
  Wire.endTransmission();
}

// deze functie leest de druk sensor op het bed uit
void readRotaryEncoder()
{
  // begin transmissie met druk sensor 
  Wire.beginTransmission(0x36);
  Wire.write(byte(0xA2));          
  Wire.write(byte(0x03));  
  Wire.endTransmission(); 

  // lees druk sensor van het bed uit
  Wire.requestFrom(0x36, 4);   
  anin0 = Wire.read()&0x03;  
  anin0=anin0<<8;
  anin0 = anin0|Wire.read();  

  itoa(anin0, buffer2, 10); // zet de integer waarde van de switch om naar een string, zodat deze over de socket verbinding gestuurd kan worden
}

// deze functie verbind met de pi en leest de data van de pi uit, vervolgens word de sensor data teruggestuurd
void connectWithClient()
{
  WiFiClient client = wifiServer.available();

  // controleer of er verbinding is met de pi
  if (client) {
    // deze while loop uitvoeren zolang de pi verbonden is
    while (client.connected()) {
      delay(20);
      // lees de pi uit als er data is
      while (client.available()>0) {  
        c = client.read();
      }
      
      turnOnLed();
      readSwitch();
      readRotaryEncoder();

      Switch.value = buffer1;
      RotaryEncoder.value = buffer2;
      sensorString = Switch.key + EndOfNumber + Switch.value + EndOfNumber + RotaryEncoder.key + EndOfNumber + RotaryEncoder.value + EndOfNumber; // string die teruggestuurd word naar de pi

      char writebuffer[50];
      strcpy(writebuffer, sensorString.c_str());

      client.write(writebuffer);  // deze functie stuurt de sensor data terug naar de pi

      delay(10);
    }
    client.stop(); // stop de verbinding met de pi, zodra de sensor data verzonden is

    Serial.println(" ");
    Serial.println("Client disconnected");
 }
}

// deze functie initialiseert de WiFi instellingen van de Wemos
void initWiFi()
{
  // verbind met WiFi
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.hostname("Wemos");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  WiFi.config(ip, GW, netmask, GW);
  
  Serial.println("");
  Serial.println("WiFi connected");
 
  // print het IP address
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  wifiServer.begin();
}
