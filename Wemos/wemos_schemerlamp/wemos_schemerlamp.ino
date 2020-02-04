#include <FastLED.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <string.h>
#define PORT 3000 
#include <cstring>

#define DATA_PIN     D5
#define NUM_LEDS    1
#define I2C_SDL    D1
#define I2C_SDA    D2

// network SSID and wachtwoord
const char* ssid = "Groep 9";
const char* password = "LekkerBelangrijk";

WiFiServer wifiServer(PORT);

// statische IP
IPAddress ip(10, 42, 0, 13);
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
}Motion;

struct Actuator {
  int key;
  int value;
}Led;

CRGB leds[NUM_LEDS];

void setup() {
  Wire.begin();
  Serial.begin(115200);
  delay(10);

  pinMode(D5, OUTPUT);

  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

  // initialiseer WiFi instellingen
  initWiFi();

  // ken key values toe aan actuatoren en sensoren
  Led.key = 8;
  Motion.key = 9;

  Led.value = 0;
}

// primaire loop   
void loop() {
  connectWithClient();
}
  
// deze functie leest de motion sensor op de schemerlamp uit
void readMotionSensor()
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

// deze functie zet de led van de schemerlamp aan
void turnOnLed()
{
  if (Led.value == 1) {
    // lamp aan als er beweging is
    leds[0] = CRGB::Gray;
    FastLED.show();
  }
  else{  
    // lamp uit als er geen beweging is
    leds[0] = CRGB::Black;  
    FastLED.show();         
  }
}

// deze functie verbind met de pi en leest de data van de pi uit, vervolgens word de sensor data teruggestuurd
void connectWithClient()
{
  WiFiClient client = wifiServer.available();
  
  if (client) {
    
    // deze while loop uitvoeren zolang de pi verbonden is
    while (client.connected()) {
      delay(20);
      // lees de pi uit als er data is
      while (client.available()>0) {
        c = client.read();
        Led.value = 0;
        // deze if statement schijt de key van de value
        if(c - '0' == 8)
        {
          c = client.read();
          Led.value = c - '0';
        }
      }
      
      readMotionSensor();
      
      Motion.value = buffer1;
      sensorString = Motion.key + EndOfNumber + Motion.value + EndOfNumber; // string die teruggestuurd word naar de pi

      char writebuffer[50];
      strcpy(writebuffer, sensorString.c_str());

      client.write(writebuffer); // deze functie stuurt de sensor data terug naar de pi
      delay(10);
    }
    client.stop(); // stop de verbinding met de pi, zodra de sensor data verzonden is

    turnOnLed();

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
