#include<WiFi.h>
#include<SPIFFS.h>
#include<FileSystem/Settings.h>

#include<ESPAsyncWebServer.h>
AsyncWebServer server(80);


extern void WriteLine(String text);
extern char* ToChar(String command);
extern bool Debug;
extern String Ssid,Password;
extern void setWiFiSettings(String ssid,String password);
extern void Reset();
//Создает точку доступа для первичной настройки
void CreateAP(String ssid,String password)
{
    WriteLine("Configurating AP:");
    WriteLine("Ssid:" + ssid);
    WriteLine("Password:" + password);
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ToChar(ssid),ToChar(password));
    WriteLine("AP Configurated");
    WriteLine("AP IP:");
    IPAddress IP = WiFi.softAPIP();
    if(Debug)
        Serial.println(IP);
}


void InitServer()
{
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/Registration/Start/index.html", "text/html");
    });
  
    server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/Registration/style.css", "text/css");
    });

    server.on("/ssid", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/Registration/Ok/index.html", "text/html");
        // GET input1 value on <ESP_IP>/get?input1=<inputMessage>
        if (request->hasParam("ssid")) {
          Ssid = request->getParam("ssid")->value();
        }
        WriteLine(Ssid);
        if (request->hasParam("password")) {
          Password = request->getParam("password")->value();
        }
        WriteLine(Password);   
        setWiFiConfigState(1);
        setWiFiSettings(Ssid,Password);
        Reset();
    });

    server.begin();
}