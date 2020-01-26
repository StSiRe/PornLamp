#include <WiFi.h>
#include <DNSServer.h>
#include <WebServer.h>
#include <FS.h>
#include <ArduinoJson.h>    
#include "SPIFFS.h"

String ssidName = "g";
String ssidPassword = "g";
String jsonConfig = "{}";
int isFirstStart = 0;
void setup() 
{
  Serial.begin(115200);
  FS_init();
  //loadConfig();
  //initWiFi(); 
  Serial.println(ssidPassword);
    
}

void loop() 
{
  
}
