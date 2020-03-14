#include<HTTPClient.h>//Нахуй не надо - но без него не работает аудио...
#include<Arduino.h>
#include<Functions.h>
#include<FileSystem/FileSys.h>
#include<Wifi/Wifi.h>
#include<Led/Display.h>
#include<Audio/Controller.h>
#include<System/Time.h>
#include<Led/Sparks.h>
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

int Dolbayob = 3;
void setup()
{
  Serial.begin(115200);
  InitLamp();
  //PlayAudio("/Sound/Notification.mp3");  
}


void loop()
{ 
  //PlayAudio("/Startup.mp3");
  ChangeAnimation("WiFiConnectionProcess");
  Delay(5000);
  ChangeAnimation("WiFiConnectionSuccess");
  Delay(7580);
  ChangeAnimation("Penis");
  Delay(30000);
  ChangeAnimation("Fire");
  Delay(10000);
  ChangeAnimation("Matrix");
  Delay(10000);
}

//ToDO Голубой ветерок! Лава И Змею!