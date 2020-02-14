#include<ESPAsyncWebServer.h>
void Init()
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

void ConfigServer()
{
    Init();



}
