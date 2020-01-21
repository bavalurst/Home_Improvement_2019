#include <Wire.h>
#include <ESP8266WiFi.h>
#include <string.h>
#define PORT 3000 
#include <cstring>
#include <Servo.h>

// network SSID and wachtwoord
const char* ssid = "Groep 9";
const char* password = "LekkerBelangrijk";

WiFiServer wifiServer(PORT);

// statische IP
IPAddress ip(10, 42, 0, 11);
IPAddress GW(10, 42, 0, 1);
IPAddress netmask(255, 255, 255, 0);

void initWiFi();
void connectWithClient();
void turnOnLeds();
void turnOnServo();
void readSwitches();

char c;
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
  String value; 
}switchBuiten, switchBinnen;

struct Actuator {
  int key;
  int value; 
}ledBuiten, ledBinnen, servoDeur;

void setup() {
  Wire.begin();
  Serial.begin(115200);

  delay(10);

  // initialiseer WiFi instellingen
  initWiFi();
  

  myservo.attach(D5);
  myservo.write(pos);

  // ken key values toe aan actuatoren en sensoren
  switchBuiten.key = "26";
  switchBinnen.key = "25";
  ledBuiten.key = 23;
  ledBinnen.key = 22;
  servoDeur.key = 24;

  // zet waardes van actuatoren op 0
  ledBinnen.value = 0;
  ledBuiten.value = 0;
  servoDeur.value = 0;
}

// primaire loop 
void loop() {
  connectWithClient();
}

// deze functie leest de switch op het bed uit
void readSwitches()
{
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x00));      
  Wire.endTransmission();
  Wire.requestFrom(0x38, 1);   
  unsigned int inputs = Wire.read();  // hier wordt de switch uitgelezen
  if (inputs % 2 == 0) // controleer of de switches zijn ingedrukt
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
  
  itoa(inputsLedBinnen, buffer1, 10); // zet de integer waarde van de switch om naar een string, zodat deze over de socket verbinding gestuurd kan worden
  itoa(inputsLedBuiten, buffer2, 10); // zet de integer waarde van de switch om naar een string, zodat deze over de socket verbinding gestuurd kan worden
}

// deze functie zet de leds op het de deur aan
void turnOnLeds()
{
  // begin transmissie met leds
  Wire.beginTransmission(0x38);
  Wire.write(byte(0x03));
  Wire.write(byte(0x0F));
  Wire.endTransmission();

  // zet led op basis van ontvangen value van de PI
  Wire.beginTransmission(0x38);
  Wire.write(byte(0x01));
  Wire.write(byte(ledBuiten.value + ledBinnen.value << 4)); // zet leds op basis van ontvangen value
  Wire.endTransmission();
}

// deze functie zet de servo op de deur aan
void turnOnServo()
{
  // deur openen als knop aan de buitenkant wordt ingedrukt
  if (servoDeur.value == 1) {                    
    pos = -30;    
    myservo.write(pos);                        
  }else if(servoDeur.value == 0)
  {
     pos = 79;
     myservo.write(pos);
  }
}

// deze functie leest de druk sensor op het bed uit
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
        ledBinnen.value = 0;
        ledBuiten.value = 0;
        //servoDeur.value = 0;

        // deze rij if en else statements zorgen ervoor dat de key en value gescheiden worden
        if(c - '0' == 2)  
        {
          c = client.read();
          if(c - '0' == 4)
          {
            c = client.read();
            servoDeur.value = c - '0';
          }else if(c - '0' == 3)
          {
            c = client.read();
            ledBuiten.value = c - '0';
          }else if(c - '0' == 2)
          {
            c = client.read();
            ledBinnen.value = c - '0';
          }
        }
      }
      
      readSwitches();

      switchBinnen.value = buffer1;
      switchBuiten.value = buffer2;
      sensorString = switchBinnen.key + EndOfNumber + switchBinnen.value + EndOfNumber + switchBuiten.key + EndOfNumber + switchBuiten.value + EndOfNumber; // string die teruggestuurd word naar de pi

      char writebuffer[50];
      strcpy(writebuffer, sensorString.c_str());

      client.write(writebuffer); // deze functie stuurt de sensor data terug naar de pi
      delay(10);
    }
    client.stop(); // stop de verbinding met de pi, zodra de sensor data verzonden is

    turnOnLeds();
    turnOnServo();

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
  WiFi.begin(ssid, password);
  WiFi.mode(WIFI_STA);
  WiFi.config(ip, GW, netmask, GW);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
 
  // print het IP address
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  wifiServer.begin();
}
