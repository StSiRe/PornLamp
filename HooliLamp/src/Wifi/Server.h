#include<stdlib.h>
#include<ArduinoJson.h>
extern void ChangeAnimation(String animationName);
extern void OnMatrix();
extern void OffMatrix();
extern void SetBrightness(int brightness);
extern int GetMaxBrightness();
extern int GetBrightness();
extern String AnimationModes[];
extern String _currentAnimation;
void AddImagesHandlers()
{
    server.on("/favicon.ico", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/Main/Images/icon.svg");
    });
    server.on("/Images/logo.svg", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/Main/Images/logo.svg");
    });
    server.on("/Images/Animations.svg", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/Main/Images/Animations.svg");
    });
    server.on("/Images/Music.svg", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/Main/Images/Music.svg");
    });
    server.on("/Images/Settings.svg", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/Main/Images/Settings.svg");
    });
    server.on("/Images/Alarm.svg", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/Main/Images/Alarm.svg");
    });
    server.on("/Images/Return.svg", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/Main/Images/Return.svg");
    });
    server.on("/Images/PowerOn.svg", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/Main/Images/PowerOn.svg");
    });
    server.on("/Images/PowerOff.svg", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/Main/Images/PowerOff.svg");
    });
    
    server.on("/Images/Plus.svg", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/Main/Images/Plus.svg");
    });
    
    server.on("/Images/Delete.svg", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/Main/Images/Delete.svg");
    });
    
    server.on("/Images/Save.svg", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/Main/Images/Save.svg");
    });
    
    server.on("/Images/MiniSettings.svg", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/Main/Images/MiniSettings.svg");
    });
    //js files
    server.on("/Animations.js", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/Main/Animations.js");
    });
    server.on("/data.js", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/Main/data.js");
    });
    server.on("/Main.js", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/Main/Main.js");
    });
    server.on("/Elements.js", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/Main/Elements.js");
    });
    
    server.on("/Alarm.js", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/Main/Alarm.js");
    });
}
void AddAnimationHandlers()
{
    server.on("/Animations/PowerState", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200,"text/html","Ok");
        String result = "On";
        if (request->hasParam("PowerState")) {
            result = request->getParam("PowerState")->value();
        }
        if(result == "On")
        {
            OnMatrix();
        }
        else
        {            
            OffMatrix();
        }
    });

    server.on("/Animations/Brightness", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200,"text/html","Ok");
        int res = 64;
        if (request->hasParam("Brightness")) 
        {
            String s = request->getParam("Brightness")->value();
            res = atoi(ToChar(s));
        }
        res *=GetMaxBrightness();
        res /=100;
        SetBrightness(res);
        //Serial.println(res);
    });
    server.on("/Animations/Data", HTTP_GET, [](AsyncWebServerRequest *request){
        String json= "";
        DynamicJsonDocument doc(512);
        doc["Brightness"] = GetBrightness() / GetMaxBrightness() * 100;
        doc["CurrentAnimation"] = _currentAnimation;
        JsonArray AnimationsList = doc.createNestedArray("AnimationsList");        
        for(int i=0;i<5;i++)
        {
            AnimationsList.add(AnimationModes[i]);
        }
        serializeJson(doc,json);
        request->send(200,"text/json",json);
        WriteLine(json);
    });
    server.on("/Images/Brightness.svg", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/Main/Images/Brightness.svg");
    });

    server.on("/Images/Previous.svg", HTTP_GET, [](AsyncWebServerRequest *request){
            request->send(SPIFFS, "/Main/Images/Previous.svg");
        });
    server.on("/Images/Next.svg", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/Main/Images/Next.svg");
    });
   

    server.on("/Animations/Animation", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200,"text/html","Ok");        
        if (request->hasParam("Animation")) 
        {
            String s = request->getParam("Animation")->value();
            ChangeAnimation(s);
        }
    });

}
void AddSoundHandlers()
{
    
}
extern std::vector<AlarmClock> AlarmClocks;
void AddAlarmHandlers()
{    
    server.on("/Alarm/Data", HTTP_GET, [](AsyncWebServerRequest *request){
        String json= "";
        DynamicJsonDocument doc(512);
        JsonArray Alarms = doc.createNestedArray("Alarms");    
        for(int i=0;i < AlarmClocks.size();i++)
        {
            JsonObject alarm = Alarms.createNestedObject();
            alarm["Hour"]  = AlarmClocks[i].Hour;
            alarm["Minute"] = AlarmClocks[i].Minute;
            alarm["Sunrise"] = AlarmClocks[i].Sunrise;
            alarm["Enabled"] = AlarmClocks[i].Enabled;
            JsonArray days = alarm.createNestedArray("Days");
            for(int j=0;j < AlarmClocks[i].Days.size();j++)
            {
                days.add(AlarmClocks[i].Days[j]);
            }       
        }
        serializeJson(doc,json);
        request->send(200,"text/json",json);
        WriteLine(json);
    });


    server.on("/Alarm/Delete", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200,"text/html","Ok");
        String result = "";
        if (request->hasParam("Delete")) 
        {
            result = request->getParam("Delete")->value();
        }
        int id = atoi(ToChar(result));
        AlarmClocks.erase(AlarmClocks.begin() + id);
    });
    server.on("/Alarm/SaveAll", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200,"text/html","Ok");
        String result = "";
        if (request->hasParam("SaveAll")) 
        {
            result = request->getParam("SaveAll")->value();
        }
        WriteLine(result);
    });
    server.on("/Alarm/Save", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200,"text/html","Ok");
        String result = "";
        if (request->hasParam("Save")) 
        {
            result = request->getParam("Save")->value();
        }
        DynamicJsonDocument doc(4096);
        deserializeJson(doc,result);
        auto id = doc["id"];        
        WriteLine(result);
        SetValue(doc["Hour"],AlarmClocks[id].Hour,0);
        SetValue(doc["Minute"],AlarmClocks[id].Minute,0);
        SetValue(doc["Enabled"],AlarmClocks[id].Enabled,false);
        int days = doc["Days"].size();
        WriteLine(days);
        std::vector<String> AlarmDays;
        for(int j = 0; j < days; j++)
        {
            String day = doc["Days"][j];
            if(j == 6)
                AlarmDays.push_back("0");
            if(day == "1" && j!=6)
                AlarmDays.push_back(String(j+1));
            WriteLine(day);
        }
        AlarmClocks[id].Days = AlarmDays;
    });
}
void AddSettingsHandlers()
{
    
}
void ConfigServer()
{
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/Main/index.html", "text/html");
        WriteLine(xPortGetCoreID());
    });
    server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/Main/style.css", "text/css");
    });
    
    AddImagesHandlers();
    AddAnimationHandlers();
    AddSettingsHandlers();
    AddSoundHandlers();
    AddAlarmHandlers();
    server.begin();
    Log.addLog("Main server was started succesfuly", "Server.h",1);
}
