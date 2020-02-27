#include<ESPAsyncWebServer.h>
void LoadAnimationImages()
{
    server.on("/Images/Animations/Brightness.png", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/Main/Images/Brightness.png");
    });
}
void Init()
{
    //Main Files
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/Main/index.html", "text/html");
    });  
    server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/Main/style.css", "text/css");
    });
    //Images
    server.on("/favicon.ico", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(SPIFFS, "/Main/Images/favicon.ico");
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


    LoadAnimationImages();
    server.begin();
}

void ConfigServer()
{
    Init();
}
