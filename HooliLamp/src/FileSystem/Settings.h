#include<SPIFFS.h>
#include<ArduinoJson.h>
bool ConfigState = false;
extern void WriteLine(String text);
extern String Ssid,Password;
void LoadData()
{
    if(!SPIFFS.exists("/Settings.json"))
    {
        WriteLine("File not exists.System`ll create new file");
        File set = SPIFFS.open("/Settings.json","w");
        set.print("");
        WriteLine("File created");
    }

    File settings = SPIFFS.open("/Settings.json");
    if(!settings)
    {
        WriteLine("System can`t open settings file");
        return;
    }

    size_t size =  settings.size();
    if(size > 1024) {
        WriteLine("File is so big"); 
        return;
    }
    WriteLine(settings.readString());
    String json = settings.readString();
    DynamicJsonDocument doc(256);
    DeserializationError error = deserializeJson(doc, json);
    if(error)
    {
        WriteLine("Deserialisation failed.Settings will be stand standart");
    }
    bool _ConfigState = doc["ConfigState"];
    ConfigState = _ConfigState;

    String _ssid = doc["WiFiSsid"];
    if(_ssid != NULL && _ssid != "" && _ssid != "null")
        Ssid = _ssid;

    String _password = doc["WiFiPassword"];
    if(_password != NULL && _password != "" && _password != "null")
        Password = _password;
    WriteLine(_password + " " + _ssid);


}

//Возвращает состояние инициализации WIFi и прочего
//true - пароль и имя точки доступа заданы; false - первичная настройка еще не пройдена
bool getWiFiConfigState()
{
    return ConfigState;
}


int GetUTC()
{
    return 3;
}

//0- non initialization; 1- setup complete
void setWiFiConfigState(bool state)
{
    ConfigState = state;
}
void setWiFiSettings(String ssid,String password)
{
    Ssid = ssid;
    Password = password;
}

void saveSettings()
{
    File settings = SPIFFS.open("/Settings.json","w");
    if(!settings)
    {
        WriteLine("System can`t open settings file");
        return;
    }

    DynamicJsonDocument doc(256);
    doc["ConfigState"] = ConfigState;
    doc["WiFiPassword"] = Ssid;
    doc["WiFiSsid"] = Password;

    String json;
    serializeJson(doc,json);
    if(settings.print(json))
    {
        WriteLine("Success saving data!");
    }
    WriteLine(settings.readString());
    WriteLine(json);
    settings.close();
}