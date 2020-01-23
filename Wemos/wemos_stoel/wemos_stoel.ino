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
IPAddress ip(10, 42, 0, 14);
IPAddress GW(10, 42, 0, 1);
IPAddress netmask(255, 255, 255, 0);

void initWiFi();
void connectWithClient();
void turnOnLed();
void readSwitch();
void readPressure();

char c = 0;
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

struct Actuator {
  int key;
  int value;
}Led, Tril;

void setup() {
  Wire.begin();
  Serial.begin(115200);
  delay(10);

  // initialiseer WiFi instellingen
  initWiFi();
  
  // ken key values toe aan actuatoren en sensoren
  Switch.key = "7";
  RotaryEncoder.key = "6";
  Led.key = 5;
  Tril.key = 4;

  Led.value = 0;
  Tril.value = 0;

  pinMode(D5, OUTPUT);
  digitalWrite(D5, LOW);

  
}

// primaire loop   
void loop() {
  connectWithClient();
}

// deze functie leest de switch op de stoel uit
void readSwitch()
{
  Wire.beginTransmission(0x38); 
  Wire.write(byte(0x00));      
  Wire.endTransmission();
  Wire.requestFrom(0x38, 1);   
  unsigned int inputs = Wire.read();  // hier wordt de switch uitgelezen
  if (inputs % 2 == 0){ // controleer of de switches zijn ingedrukt
     inputs = 0;
  }
  else {
    inputs = 1;
  }
  
  itoa(inputs, buffer1, 10); // zet de integer waarde van de switch om naar een string, zodat deze over de socket verbinding gestuurd kan worden
}

// deze functie zet de led en/of het trilelement aan
void turnOnLedAndTril()
{
  // begin transmissie met actuatoren
  Wire.beginTransmission(0x38);
  Wire.write(byte(0x03));
  Wire.write(byte(0x0F));
  Wire.endTransmission();

  // zet actuatoren op basis van ontvangen value van de pi
  Wire.beginTransmission(0x38);
  Wire.write(byte(0x01));
  Serial.print("Led 2: ");
  Serial.println(Led.value);
  Serial.print("Tril 2: ");
  Serial.println(Tril.value);
  Wire.write(byte(Led.value + Tril.value << 4)); // zet led op basis van ontvangen value
  Wire.endTransmission();
}

// deze functie leest de druk sensor op de stoel uit
void readPressure()
{
  Wire.beginTransmission(0x36);
  Wire.write(byte(0xA2));          
  Wire.write(byte(0x03));  
  Wire.endTransmission(); 

 // begin transmissie met druk sensor
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
      while (client.available()>0) {
        c = client.read();
        Led.value = 0;
        Tril.value = 0;
        Serial.print("Led 1: ");
        Serial.println(Led.value);
        Serial.print("Tril 1: ");
        Serial.println(Tril.value);
        Serial.print("C1: ");
        Serial.println(c);
        // deze rij if en else statements zorgen ervoor dat de key en value gescheiden worden
        if(c - '0' == 5)
        {
          c = client.read();
          Serial.print("C2: ");
          Serial.println(c);
          Led.value = c - '0';
        }else if(c - '0' == 4)
        {
          c = client.read();
          Serial.print("C3: ");
          Serial.println(c);
          Tril.value = c - '0';
        }
      }
  
      readSwitch();
      readPressure();

      Switch.value = buffer1;
      RotaryEncoder.value = buffer2;
      sensorString = Switch.key + EndOfNumber + Switch.value + EndOfNumber + RotaryEncoder.key + EndOfNumber + RotaryEncoder.value + EndOfNumber; // string die teruggestuurd word naar de pi

      char writebuffer[50];
      strcpy(writebuffer, sensorString.c_str());

      client.write(writebuffer); // deze functie stuurt de sensor data terug naar de pi
      delay(10);
    }
    client.stop(); // stop de verbinding met de pi, zodra de sensor data verzonden is

    turnOnLedAndTril();

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
