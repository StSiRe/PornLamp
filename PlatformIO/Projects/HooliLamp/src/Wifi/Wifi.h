#include<WiFi.h>
#include<Wifi/Setup.h>


extern void WriteLine(String text);
extern bool getWiFiConfigState();
extern void setWiFiConfigState();
extern void CreateAP(String ssid,String password);
extern void InitServer();
extern char* ToChar(String command);
extern String Ssid,Password;
extern bool ConfigMDNS();


void ConfigWiFi()
{
    WiFi.begin(ToChar(Ssid),ToChar(Password));
    while (WiFi.status() != WL_CONNECTED) 
    {      
        vTaskDelay(500/15);
    }
    WriteLine(WiFi.localIP().toString());
    ConfigMDNS();//Надо будет проверить - получилось ли 
}

void WiFiStart()
{
    if(!getWiFiConfigState())//Если система не была проинициализированна
    {
        CreateAP(Ssid,Password);
        InitServer();
        return;
    }
    ConfigWiFi();
}


