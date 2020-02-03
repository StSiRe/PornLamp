#include<SPIFFS.h>
#include<ArduinoJson.h>
#define FS SPIFFS 

extern void WriteLine(String text);
void LoadData()
{
    if(FS.exists("/Settings.json"))
    {
        WriteLine("File not exists.System`ll create new file");
        File set = SPIFFS.open("/Settings.json","w");
        set.write(0);
        WriteLine("File created");
    }

    File settings = FS.open("/Settings.json");
    if(!settings)
    {
        WriteLine("System can`t open settings file");
    }

    size_t size =  settings.size();
    if(size > 1024) {WriteLine("File is so big"); return;}


    DynamicJsonDocument

}
bool getWiFiConfigState()
{
    return false;
}

//0- non initialization; 1- setup complete
void setWiFiConfigState(int state)
{
    //anything
}
void setWiFiSettings(String ssid,String password)
{

}

void saveSettings()
{

}