#include <Wire.h>
#include <ESP8266WiFi.h>
#include <string.h>
#define PORT 3000 
#include <cstring>
#include <Servo.h>

// Network SSID
const char* ssid = "Wij gebruiken een IDE";
const char* password = "Mijnarends";

WiFiServer wifiServer(PORT);
IPAddress ip(10, 42, 0, 11);
IPAddress GW(10, 42, 0, 1);
IPAddress netmask(255, 255, 255, 0);

void initWiFi();
void connectWithClient();
void turnOnLeds();
void turnOnServo();
void readSwitches();

char c = 0;
unsigned int anin0 = 0;
unsigned int anin1 = 0;

int pos = 79;
unsigned int inputsLedBuiten = 0;
unsigned int inputsLedBinnen = 0;

char buffer1[20];
char buffer2[20];
String sensorString;
String EndOfNumber = ";";

Servo myservo; 

struct Sensor {
  String key;
  String value = "0"; 
}switchBuiten, switchBinnen;

struct Actuator {
  int key;
  unsigned int value = 0; 
}ledBuiten, ledBinnen, servoDeur;

void setup() {
  Wire.begin();
  Serial.begin(115200);
  delay(10);

  initWiFi();
  

  myservo.attach(D5);
  myservo.write(pos);

  switchBuiten.key = "26";
  switchBinnen.key = "25";
  ledBuiten.key = 23;
  ledBinnen.key = 22;
  servoDeur.key = 24;

  ledBinnen.value = 0;
  ledBuiten.value = 0;
  servoDeur.value = 0;
}
 
void loop() {
  connectWithClient();
}

void readSwitches()
{
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x00));      
  Wire.endTransmission();
  Wire.requestFrom(0x38, 1);   
  unsigned int inputs = Wire.read();  
  if (inputs % 2 == 0)
  {
     if((inputs&0x02) / 2 == 1)
     {
      inputsLedBuiten = 2;
     }else
     {
      inputsLedBinnen = 0;
      inputsLedBuiten = 0;
     }
  }else 
  {
    inputsLedBinnen = 1;
  }
  
  itoa(inputsLedBinnen, buffer1, 10);
  itoa(inputsLedBuiten, buffer2, 10);
}

void turnOnLeds()
{
  
  // Begin transmissie met leds
  Wire.beginTransmission(0x38);
  Wire.write(byte(0x03));
  Wire.write(byte(0x0F));
  Wire.endTransmission();

  // Zet led op basis van ontvangen state van de PI
  Wire.beginTransmission(0x38);
  Wire.write(byte(0x01));
  Serial.print("Led buiten + Led binnen : ");
  Serial.println(ledBuiten.value + ledBinnen.value);
  Serial.print("Led buiten: ");
  Serial.println(ledBuiten.value);
  Serial.print("Led binnen : ");
  Serial.println(ledBinnen.value);
//  if((ledBuiten + ledBinnen) == -48)
//  {
//   led = 0;
//  }else if(ledBuiten + ledBinnen) == -49)
//  (
//    led = 1
//  }else if(ledBuiten + ledBinnen) == -50)
//  {
//    led = 2
//  }
  Wire.write(byte(ledBuiten.value + ledBinnen.value << 4)); // zet led op basis van ontvangen state
  Wire.endTransmission();
}

void turnOnServo()
{
  // deur openen als knop aan de buitenkant wordt ingedrukt
  if (servoDeur.value == 1) {                    
    for (pos = 79; pos >= -30; pos -= 1) {        
      myservo.write(pos);                        
      delay(10);
    }
    ledBinnen.value = 1;
    servoDeur.value = 3; 
  }
   // deur sluiten na ontvangen 0
  if(servoDeur.value == 0)
  {
     for (pos = -30; pos <= 79; pos += 1) {        // deur sluiten na ontvangen 0
     myservo.write(pos);
     delay(10);
     }  
     ledBinnen.value = 0;
     servoDeur.value = 3; 
  }
}


void connectWithClient()
{
  WiFiClient client = wifiServer.available();
  
  if (client) {
 
    while (client.connected()) {
      delay(20);
      while (client.available()>0) {
        c = client.read();
        ledBinnen.value = 0;
        ledBuiten.value = 0;
        servoDeur.value = 0;
        Serial.print("C1: ");
        Serial.println(c);
        if(c - '0' == 2)
        {
          c = client.read();
          Serial.print("C2: ");
          Serial.println(c);
          if(c - '0' == 4)
          {
            c = client.read();
            Serial.print("C3: ");
            Serial.println(c);
            servoDeur.value = c - '0';
            Serial.print("servoDeur: ");
            Serial.println(servoDeur.value);
            turnOnServo();
            break;
          }else if(c - '0' == 3)
          {
            c = client.read();
            Serial.print("C4: ");
            Serial.println(c);
            ledBuiten.value = c - '0';
          }else if(c - '0' == 2)
          {
            c = client.read();
            Serial.print("C5: ");
            Serial.println(c);
            ledBinnen.value = c - '0';
          }
        }
      }
      
      readSwitches();

      switchBinnen.value = buffer1;
      switchBuiten.value = buffer2;
      sensorString = switchBinnen.key + EndOfNumber + switchBinnen.value + EndOfNumber + switchBuiten.key + EndOfNumber + switchBuiten.value + EndOfNumber;

      char writebuffer[50];
      strcpy(writebuffer, sensorString.c_str());
      client.write(writebuffer);
      delay(10);
    }
    client.stop();

    turnOnLeds();

    Serial.println(sensorString);
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
