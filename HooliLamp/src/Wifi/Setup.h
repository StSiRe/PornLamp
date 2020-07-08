#include<ESPAsyncWebServer.h>
AsyncWebServer server(80);
String _ssid,_password;

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
    WriteLine(IP);
    Log.addLog("AP created with parametrs (Ssid: " + ssid + ", Password: " + password + ")");
}

void SaveWiFiSetupData(void *pv)
{
    WriteLine("Saving ssid and password started");
    Delay(1000);
    setWiFiConfigState(true);
    setWiFiSettings(_ssid,_password);
    Reset();
    vTaskDelete(NULL);//Нахуй не сделаось,но пусть будет
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
          _ssid = request->getParam("ssid")->value();
        }
        WriteLine(_ssid);
        if (request->hasParam("password")) {
          _password = request->getParam("password")->value();
        }
        WriteLine(_password);   
        
        xTaskCreatePinnedToCore(SaveWiFiSetupData,"WiFi Initialization",8192,NULL,1,NULL,0);
    });

    server.begin();
}