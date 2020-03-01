#include<WiFi.h>
#include<SPIFFS.h>
#include<FileSystem/Settings.h>
//#include<ESPAsyncWebServer.h>
//AsyncWebServer server(80);
String _ssid,_password;

extern void WriteLine(String text);
extern char* ToChar(String command);
extern bool Debug;
extern void setWiFiSettings(String ssid,String password);
extern void Reset();
extern void Delay(int milliseconds);
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
    {
        Serial.println(IP);
    }  
}

void SaveData(void *pv)
{
    WriteLine("Saving ssid and password started");
    Delay(1000);
    setWiFiConfigState(1);
    setWiFiSettings(_ssid,_password);
    Reset();
    vTaskDelete(NULL);//Нахуй не сделаось,но пусть будет
}
void InitServer()
{
    /*
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
          _ssid = request->getParam("ssid")->value();
        }
        WriteLine(_ssid);
        if (request->hasParam("password")) {
          _password = request->getParam("password")->value();
        }
        WriteLine(_password);   
        
        xTaskCreatePinnedToCore(SaveData,"Ssid Saver",8096,NULL,1,NULL,0);
    });

    server.begin();
    */
}