#include<HTTPClient.h>//Нахуй не надо - но без него не работает аудио...
#include<Arduino.h>
#include<Functions.h>
#include<FileSystem/FileSys.h>
#include<Wifi/Wifi.h>
#include<Led/Display.h>
#include<Audio/Controller.h>
#include<Led/Animations.h>

String Ssid="Hooli.Lamp",Password="12345678";

void InitLamp()
{
  InitMatrix();
  ConfigFS();
  LoadData();
  WiFiStart();
  InitAnimations();
}


void setup()
{
  Serial.begin(115200);
  InitLamp();
  //PlayAudio("/Startup.mp3");  
  Delay(1000);
}


void loop()
{ 
  //PlayAudio("/Startup.mp3");
  ChangeAnimation("WiFiConnectionProcess");
  Delay(8316);
  ChangeAnimation("WiFiConnectionSuccess");
  Delay(7580);
  ChangeAnimation("Penis");
  Delay(10000);
}