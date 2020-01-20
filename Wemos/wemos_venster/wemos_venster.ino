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

// Network SSID
const char* ssid = "Groep 9";
const char* password = "LekkerBelangrijk";

WiFiServer wifiServer(PORT);
IPAddress ip(10, 42, 0, 15);
IPAddress GW(10, 42, 0, 1);
IPAddress netmask(255, 255, 255, 0);

void initWiFi();
void connectWithClient();
void turnOnLed();
void turnOnWindow();
void readLdrAndRotaryEncoder();

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
}LDR, RotaryEncoder;

struct Actuator {
  int key = 0;
  int value = 0;
}Led, Window;

CRGB leds[NUM_LEDS];

void setup() {
  Wire.begin();
  Serial.begin(115200);
  delay(10);

  pinMode(D5, OUTPUT);

  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

  initWiFi();

  Led.key = 14;
  Window.key = 15;
  RotaryEncoder.key = "16";
  LDR.key = "17";
}
 
void loop() {
  connectWithClient();
}

void readLdrAndRotaryEncoder()
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
  anin0 = anin0|Wire.read();  // LDR

  anin1 = Wire.read() & 0x03;    
  anin1 = anin1 << 8;                        
  anin1 = anin1 | Wire.read(); // rotary encoder
  anin1 = anin1 / 25;
     
  itoa(anin1, buffer2, 10);
  itoa(anin0, buffer3, 10);
}

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

void turnOnLed()
{
  if (Led.value > 0) {
    // lamp aan als er beweging is
    leds[0] = CRGB::Gray;
    leds[1] = CRGB::Gray;
    leds[2] = CRGB::Gray;
    FastLED.setBrightness(Led.value/40*6);        // Felheid leds
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

void connectWithClient()
{
  WiFiClient client = wifiServer.available();
  
  if (client) {
 
    while (client.connected()) {
 
      while (client.available()>0) {
        c = client.read();
        if(c - '0' == 1)
        {
          c = client.read();
          if(c - '0' == 4)
          {
            c = client.read();
            Led.value = c - '0';
            if(client.available()>0)
            {
              c = client.read();
              Led.value = Led.value * 10 + (c - '0');
            }
          }else if(c - '0' == 5)
          {
            c = client.read();
            Window.value = c - '0';
          }
        }
        
      }
      turnOnLed();
      turnOnWindow();
      readLdrAndRotaryEncoder();
      
      RotaryEncoder.value = buffer2;
      LDR.value = buffer3;
      sensorString = LDR.key + EndOfNumber + LDR.value + EndOfNumber + RotaryEncoder.key + EndOfNumber + RotaryEncoder.value + EndOfNumber;

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
