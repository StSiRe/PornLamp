#include<HTTPClient.h>//Нахуй не надо - но без него не работает аудио...
#include<Arduino.h>
#include<Functions.h>


#include<FileSystem/FileSys.h>
#include<FileSystem/Settings.h>


#include<Wifi/Wifi.h>

#include<Audio/Controller.h>

#include<Led/Display.h>
#include<Led/Animations.h>

#include<System/Time.h>

String Ssid="Hooli.Lamp",Password="12345678";

void InitLamp()
{
  InitMatrix();
  InitAnimations();

  ConfigFS();
  LoadData();

  InitWiFi();
  Delay(500);
  InitTime();
}



void setup()
{
  Serial.begin(115200);
  InitLamp();
}


void loop()
{ 
  Delay(10000);
  saveSettings();
}

//ToDO Голубой ветерок! Лава И Змею!