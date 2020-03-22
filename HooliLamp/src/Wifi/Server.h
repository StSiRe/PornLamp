#include<ESPAsyncWebServer.h>
#include<SPIFFS.h>
#include <stdlib.h>
#include<ArduinoJson.h>
extern void ChangeAnimation(String animationName);
extern void OnMatrix();
extern void OffMatrix();
extern void ChangeBrightness(int brightness);
extern char* ToChar(String command);
extern int GetBrightness();
extern String AnimationModes[];
extern String _currentAnimation;
void AddImagesHandlers()
{
    server.on("/favicon.ico", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/Main/Images/icon.png");
    });
    server.on("/Images/logo.png", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/Main/Images/logo.png");
    });
    server.on("/Images/Animations.png", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/Main/Images/Animations.png");
    });
    server.on("/Images/Music.png", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/Main/Images/Music.png");
    });
    server.on("/Images/Settings.png", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/Main/Images/Settings.png");
    });
    server.on("/Images/Alarm.png", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/Main/Images/Alarm.png");
    });
    server.on("/Images/Return.svg", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/Main/Images/Return.svg");
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
        res *=255;
        res /=100;
        ChangeBrightness(res);
        //Serial.println(res);
    });
    server.on("/Animations/Data", HTTP_GET, [](AsyncWebServerRequest *request){
        String json= "";
        DynamicJsonDocument doc(512);
        doc["Brightness"] = GetBrightness();
        doc["CurrentAnimation"] = _currentAnimation;
        JsonArray AnimationsList = doc.createNestedArray("AnimationsList");        
        for(int i=0;i<5;i++)
            AnimationsList.add(AnimationModes[i]);

        serializeJson(doc,json);
        request->send(200,"text/json",json);
        Serial.println(json);
    });
    server.on("/Images/Brightness.png", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/Main/Images/Brightness.png");
    });

    server.on("/Images/previous.png", HTTP_GET, [](AsyncWebServerRequest *request){
            request->send(SPIFFS, "/Main/Images/previous.png");
        });
    server.on("/Images/next.png", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/Main/Images/next.png");
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
void AddAlarmHandlers()
{

}
void AddSettingsHandlers()
{
    
}
void ConfigServer()
{
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/Main/index.html", "text/html");
        Serial.println(xPortGetCoreID());
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
}
