#include<HTTPClient.h>//Нахуй не надо - но без него не работает аудио...
#include<Arduino.h>
#include<Audio/mp3.h>
#include<Functions.h>
#include<FileSystem/FileSys.h>
#include<Wifi/Wifi.h>
#include<Led/Display.h>
#include<Led/Animations.h>
#include<System/Time.h>
#include<System/Status.h>


String Ssid="Hooli.Lamp",Password="12345678";

void InitLamp()
{
  WriteLine("Hooli.Lamp is loading...");
  InitSystemWD();
  InitMatrix();
  InitAnimations();
  ChangeAnimation("LampOn");
  ConfigFS();
  LoadData();
  WiFiStart();
  Delay(1000);
  InitTime();
}
void setup()
{
  Serial.begin(115200);
  InitLamp();
  WriteLine("Initialization is success!");
}


void loop()
{
  Delay(50);//As WatchDog
}