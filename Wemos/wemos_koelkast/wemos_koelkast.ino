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
IPAddress ip(10, 42, 0, 12);
IPAddress GW(10, 42, 0, 1);
IPAddress netmask(255, 255, 255, 0);

void initWiFi();
void connectWithClient();
void turnOnFan();
void turnOnCooler();
void readSwitch();
void readTempSensors();

char c;
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
  int key;
  int value;
}Fan, Cooler;

void setup() {
  Wire.begin();
  Serial.begin(115200);
  
  pinMode(D5, OUTPUT); 
  
  delay(10);

  // initialiseer WiFi instellingen
  initWiFi();

  // ken key values toe aan actuatoren en sensoren
  Switch.key = "21";
  tempFridge.key = "19";
  tempHeatsink.key = "20";
  Fan.key = 18;

  Fan.value = 1;
  Cooler.value = 1;
}
 
// primaire loop  
void loop() {
  connectWithClient();
}

// deze functie leest de switch op de koelkast uit
void readSwitch()
{
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x00));      
  Wire.endTransmission();
  Wire.requestFrom(0x38, 1);   
  unsigned int inputs = Wire.read();  // hier wordt de switch uitgelezen
  if (inputs % 2 == 0) // controleer of de switches zijn ingedrukt
     inputs = 0;
  }
  else {
    inputs = 1;
  }
  
  itoa(inputs, buffer1, 10); // zet de integer waarde van de switch om naar een string, zodat deze over de socket verbinding gestuurd kan worden
}

// deze functie zet de fan op de koelkast aan
void turnOnFan()
{ 
  // begin transmissie met leds
  Wire.beginTransmission(0x38);
  Wire.write(byte(0x03));
  Wire.write(byte(0x0F));
  Wire.endTransmission();

  // zet led op basis van ontvangen value van de pi
  Wire.beginTransmission(0x38);
  Wire.write(byte(0x01));
  Wire.write(byte(Fan.value << 4)); // zet led op basis van ontvangen value
  Wire.endTransmission();
}

// deze functie zet het koelelement op de koelkast aan
void turnOnCooler()
{ 
  digitalWrite(D5, Cooler.value);     // zet koelelement value op basis van ontvangen data 
}

// deze functie leest de temperatuur sensoren in de koelkast en op de heatsink uit
void readTempSensors()
{ 
  // begin transmissie met temperatuur sensoren
  Wire.beginTransmission(0x36);
  Wire.write(byte(0xA2));          
  Wire.write(byte(0x03));  
  Wire.endTransmission(); 

  // lees temperatuur sensor uit
  Wire.requestFrom(0x36, 4);   
  anin0 = Wire.read()&0x03;  
  anin0=anin0<<8;
  anin0 = anin0|Wire.read();  // temperatuur sensor in de koelkast

  unsigned int anin1 = Wire.read() & 0x03;    
  anin1 = anin1 << 8;                        
  anin1 = anin1 | Wire.read(); // temperatuur sensor op de heatsink
     
  itoa(anin1, buffer2, 10); // zet de integer waarde van de switch om naar een string, zodat deze over de socket verbinding gestuurd kan worden
  itoa(anin0, buffer3, 10); // zet de integer waarde van de switch om naar een string, zodat deze over de socket verbinding gestuurd kan worden
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
        Fan.value = 1;
        Cooler.value = 1;
        // deze rij if en else statements zorgen ervoor dat de key en value gescheiden worden
        if(c - '0' == 1)  
        {
          c = client.read();
          if(c - '0' == 8)
          {
            c = client.read();
            Fan.value = c - '0';
            Cooler.value = c - '0';
          }
        }
      }

      readSwitch();
      readTempSensors();

      Switch.value = buffer1;
      tempFridge.value = buffer2;
      tempHeatsink.value = buffer3;
      sensorString = Switch.key + EndOfNumber + Switch.value + EndOfNumber + tempFridge.key + EndOfNumber + tempFridge.value + EndOfNumber; // string die teruggestuurd word naar de pi

      char writebuffer[50];
      strcpy(writebuffer, sensorString.c_str()); 

      client.write(writebuffer); // deze functie stuurt de sensor data terug naar de pi
      delay(10);
    }
    client.stop(); // stop de verbinding met de pi, zodra de sensor data verzonden is
 
    turnOnFan();
    turnOnCooler();
    
    Serial.println(" ");
    Serial.println("Client disconnected")
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
