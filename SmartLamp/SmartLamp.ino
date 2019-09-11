#include <WiFi.h>
#include <DNSServer.h>
#include <WebServer.h>
#include "Strip.h"
#include <FS.h>
#include <ArduinoJson.h>    
#include "SPIFFS.h"

#define stripPinR 5
#define stripPinG 19
#define stripPinB 18
#define stripFrequency 20000
#define stripResolution 8

Strip strip(stripPinR, stripPinG, stripPinB);
String ssidName = "g";
String ssidPassword = "g";
String jsonConfig = "{}";
int isFirstStart = 0;
void setup() 
{
  Serial.begin(115200);
  FS_init();
  loadConfig();
  initWiFi(); 
  
  Serial.println(ssidPassword);
  strip.Init(stripFrequency,stripResolution);
    
}

void loop() 
{
  
  strip.sunrise();
  //strip.rainbow();
}
