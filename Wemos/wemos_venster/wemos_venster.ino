#include <FastLED.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <string.h>
#define PORT 3000 
#include <cstring>

#define DATA_PIN     D5
#define NUM_LEDS    3
#define I2C_SDL    D1
#define I2C_SDA    D2

// network SSID and wachtwoord
const char* ssid = "Groep 9";
const char* password = "LekkerBelangrijk";

WiFiServer wifiServer(PORT);

// statische IP
IPAddress ip(10, 42, 0, 15);
IPAddress GW(10, 42, 0, 1);
IPAddress netmask(255, 255, 255, 0);

void initWiFi();
void connectWithClient();
void turnOnLed();
void turnOnWindow();
void readLdrAndRotaryEncoder();

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
}LDR, RotaryEncoder;

struct Actuator {
  int key;
  int value;
}Led, Window;

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
  Led.key = 14;
  Window.key = 15;
  RotaryEncoder.key = "16";
  LDR.key = "17";

  Led.value = 0;
  Window.value = 0;
}
 
// primaire loop   
void loop() {
  connectWithClient();
}

// deze functie leest de LDR en rotary encoder uit 
void readLdrAndRotaryEncoder()
{
  // begin transmissie met analoge sensoren
  Wire.beginTransmission(0x36);
  Wire.write(byte(0xA2));          
  Wire.write(byte(0x03));  
  Wire.endTransmission(); 

  // lees LDR uit
  Wire.requestFrom(0x36, 4);   
  anin0 = Wire.read()&0x03;  
  anin0=anin0<<8;
  anin0 = anin0|Wire.read();

  // lees rotary encoder uit
  anin1 = Wire.read() & 0x03;    
  anin1 = anin1 << 8;                        
  anin1 = anin1 | Wire.read();
  anin1 = anin1 / 110;  // delen door 110 zodat er 9 niveaus van helderheid mogelijk is
     
  itoa(anin1, buffer2, 10); // zet de integer waarde van de switch om naar een string, zodat deze over de socket verbinding gestuurd kan worden
  itoa(anin0, buffer3, 10); // zet de integer waarde van de switch om naar een string, zodat deze over de socket verbinding gestuurd kan worden
}

// deze functie verduisterd het raam
void turnOnWindow()
{
  // Begin transmissie met leds
  Wire.beginTransmission(0x38);
  Wire.write(byte(0x03));
  Wire.write(byte(0x0F));
  Wire.endTransmission();

  // Zet led op basis van ontvangen state van de PI
  Wire.beginTransmission(0x38);
  Wire.write(byte(0x01));
  Wire.write(byte(Window.value << 4)); // zet led op basis van ontvangen state
  Wire.endTransmission();
}

// deze functie zet de ledstrip aan
void turnOnLed()
{
  if (Led.value > 0) {
    // lamp aan als er beweging is
    leds[0] = CRGB::Gray;
    leds[1] = CRGB::Gray;
    leds[2] = CRGB::Gray;
    FastLED.setBrightness(Led.value * 28);        // Felheid leds
    FastLED.show();
  }
  else{  
    // lamp uit als er geen beweging is
    leds[0] = CRGB::Black; 
    leds[1] = CRGB::Black; 
    leds[2] = CRGB::Black;  
    FastLED.show();         
  }
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
        Led.value = 0;
        Window.value = 0;

        // deze rij if en else statements zorgen ervoor dat de key en value gescheiden worden
        if(c - '0' == 1)
        {
          c = client.read();
          if(c - '0' == 4)
          {
            c = client.read();
            Led.value = c - '0';
          }else if(c - '0' == 5)
          {
            c = client.read();
            Window.value = c - '0';
          }
        } 
      }

      readLdrAndRotaryEncoder();
      
      RotaryEncoder.value = buffer2;
      LDR.value = buffer3;
      sensorString = LDR.key + EndOfNumber + LDR.value + EndOfNumber + RotaryEncoder.key + EndOfNumber + RotaryEncoder.value + EndOfNumber; // string die teruggestuurd word naar de pi

      char writebuffer[50];
      strcpy(writebuffer, sensorString.c_str());

      client.write(writebuffer); // deze functie stuurt de sensor data terug naar de pi
      delay(10);
    }
    client.stop(); // stop de verbinding met de pi, zodra de sensor data verzonden is

    turnOnLed();
    turnOnWindow();

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
