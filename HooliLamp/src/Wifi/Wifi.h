#include<WiFi.h>
#include<Wifi/Setup.h>
#include<Wifi/Server.h>
#include<Wifi/DNS.h>
extern String Ssid,Password;
extern void ChangeAnimation(String animationName);
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
            vTaskDelete(NULL);//Удаляем эту задачу
        }
        else
        {
            ChangeAnimation("WiFiConnectionProcess");
            waitingTimer++;
            if(waitingTimer == 120 * 3)//120 per munite and wait 3 minute
            {
                //Animation "No WiFi"
            }
            if(waitingTimer == 120 * 4)//120 per munite and wait 4 minute
            {
                Log.addLog("4 minutes left without WiFi connection - system will be reboot with standart settings", "WiFi.h");
                setWiFiConfigState(false);
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
        //WriteLine("WiFi can`t connect to AP.System will be reboot");
        Log.addLog("WiFi can`t connect to AP.System will be reboot", "WiFi.h", -1);
        Reset();
    }    
}
void onWiFiConnected(WiFiEvent_t event, WiFiEventInfo_t info)
{
    //WriteLine("WiFi connected");
    Log.addLog("WiFi connected", "WiFi.h", 1);
    ChangeAnimation("WiFiConnectionSuccess");
    WiFi.onEvent(onWiFiDisconnected,SYSTEM_EVENT_STA_DISCONNECTED);//Событие -  если нас вдруг отключили    
    WriteLine(WiFi.localIP().toString());
    ConfigMDNS();//Надо будет проверить - получилось ли 
    
}
void ConfigWiFi()
{    
    WiFi.begin(ToChar(Ssid),ToChar(Password));
    WiFi.onEvent(onWiFiConnected,SYSTEM_EVENT_STA_CONNECTED);
    Log.addLog("Trying to connect via WiFi", "WiFi.h");
    xTaskCreatePinnedToCore(WiFiViewer,"WiFi viewer",2048,NULL,1,&TaskWiFiViewer,0);
}
void InitWiFi()
{
    if(!getWiFiConfigState())//Если система не была проинициализированна
    {
        CreateAP(Ssid,Password);
        InitServer();
        return;
    }
    ConfigWiFi();
    ConfigServer();
}


