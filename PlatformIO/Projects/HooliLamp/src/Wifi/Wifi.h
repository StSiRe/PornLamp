#include<WiFi.h>
#include<Wifi/Setup.h>
#include<Wifi/Server.h>
#include<Wifi/DNS.h>
extern void WriteLine(String text);
extern bool getWiFiConfigState();
extern void setWiFiConfigState();
extern void CreateAP(String ssid,String password);
extern void InitServer();
extern char* ToChar(String command);
extern String Ssid,Password;
extern bool ConfigMDNS();
extern void Reset();
extern void WiFiConnectionProcess();
extern void WiFiConnectionSuccess();

TaskHandle_t TaskWiFiViewer;

//Выполняет отслеживание состояния WiFi подключения
void WiFiViewer(void *pvParameter)
{
    int waitingTimer = 0;
    for(;;)
    {
        vTaskDelay(500/ portTICK_RATE_MS);//Ждем пол секунды 
        bool isConnected = WiFi.isConnected();//Проверяем статус подключения
        if(isConnected)
        {
            waitingTimer= 0;
            WriteLine("WiFi viewer task deleted");
            //WiFiConnectionSuccess();
            vTaskDelete(NULL);//Удаляем эту задачу
        }
        else
        {
            //WiFiConnectionProcess();
            waitingTimer++;
            if(waitingTimer == 120 * 3)//120 per munite and wait 4 minute
            {
                //Animation "No WiFi"
            }
            if(waitingTimer == 120 * 4)//120 per munite and wait 4 minute
            {
                WriteLine("4 minutes left - system will be reboot with standart settings");
                setWiFiConfigState(0);
                Reset();
            }
        }
    }
}
void onWiFiDisconnected(WiFiEvent_t event, WiFiEventInfo_t info)
{
    WriteLine("WiFi event - lamp disconnected from ap");
    bool s = WiFi.reconnect();
    if (s)
    {
        WriteLine("WiFi can`t connect to AP.System will be reboot");
        Reset();
    }    
}
void onWiFiConnected(WiFiEvent_t event, WiFiEventInfo_t info)
{
    WriteLine("WiFi connected");
    WiFi.onEvent(onWiFiDisconnected,SYSTEM_EVENT_STA_DISCONNECTED);//Событие -  если нас вдруг отключили    
    WriteLine(WiFi.localIP().toString());
    ConfigMDNS();//Надо будет проверить - получилось ли 
}
void ConfigWiFi()
{    
    WiFi.begin(ToChar(Ssid),ToChar(Password));
    WiFi.onEvent(onWiFiConnected,SYSTEM_EVENT_STA_CONNECTED);
    xTaskCreatePinnedToCore(WiFiViewer,"WiFi viewer",2048,NULL,1,&TaskWiFiViewer,0);
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
    //LoadServer();
}


