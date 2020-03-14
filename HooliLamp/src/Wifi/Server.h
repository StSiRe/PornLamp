#include<ESPAsyncWebServer.h>
#include<SPIFFS.h>
#include <stdlib.h>

extern void ChangeAnimation(String animationName);
extern void ChangeBrightness(int brightness);
extern char* ToChar(String command);
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
    //js files
    server.on("/Animations.js", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/Main/Animations.js");
    });
    server.on("/data.js", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/Main/data.js");
    });
}
void AddAnimationHandlers()
{
    server.on("/Animations/PowerMode", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200,"text/html","Ok");
        String result = "On";
        if (request->hasParam("On")) {
          result = request->getParam("On")->value();
        }
        if (request->hasParam("Off")) {
          result = request->getParam("Off")->value();
        }
        ChangeAnimation(result);
        WriteLine("PowerMode: " + result);
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
    server.on("/Animations/Brightness.png", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/Main/Images/Brightness.png");
    });
}
void AddSoundHandlers()
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

    server.begin();
}
