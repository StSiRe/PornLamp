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
#include<System/Alarm/Dawn.h>
#include<System/Status.h>
#include<System/DeepSleep.h>


#include<Button/Button.h>

String Ssid="Hooli.Lamp",Password="12345678";

void InitLamp()
{
  
  InitMatrix();
  SetBrightness(64);
  InitAnimations();

  ConfigFS();
  LoadData();
  SetBrightness(64);

  InitWiFi();
  Delay(500);
  
  InitTime();
  InitAlarmClock();
  
  InitSystemWD();

  InitButton();
}



void setup()
{
  Serial.begin(115200);
  InitLamp();
  OnMatrix();
}


void loop()
{ 
}

//ToDO Голубой ветерок! Лава И Змею!