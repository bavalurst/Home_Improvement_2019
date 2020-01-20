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

// Network SSID
const char* ssid = "Groep 9";
const char* password = "LekkerBelangrijk";

WiFiServer wifiServer(PORT);
IPAddress ip(10, 42, 0, 13);
IPAddress GW(10, 42, 0, 1);
IPAddress netmask(255, 255, 255, 0);

void initWiFi();
void connectWithClient();
void turnOnLed();
void readSwitch();
void readRotaryEncoder();

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
}Motion;

struct Actuator {
  int key = 0;
  int value = 0;
}Led;

CRGB leds[NUM_LEDS];

void setup() {
  Wire.begin();
  Serial.begin(115200);
  delay(10);

  pinMode(D5, OUTPUT);

  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

  initWiFi();

  Led.key = 5;
  Motion.key = 9;
}
 
void loop() {
  connectWithClient();
}

void readMotionSensor()
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

void turnOnLed()
{
  if (c - '0' == 1) {
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

void connectWithClient()
{
  WiFiClient client = wifiServer.available();
  
  if (client) {
 
    while (client.connected()) {
 
      while (client.available()>0) {
        c = client.read();
      }
      turnOnLed();
      readMotionSensor();
      Motion.value = buffer1;
      sensorString = Motion.key + EndOfNumber + Motion.value + EndOfNumber;

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
