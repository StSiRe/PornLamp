#include<HTTPClient.h>//Нахуй не надо - но без него не работает аудио...
#include<Arduino.h>
#include<Functions.h>
#include<FileSystem/FileSys.h>
#include<Wifi/Wifi.h>
#include<Led/Display.h>
#include<Led/Fire.h>
#include<Audio/Controller.h>

String Ssid="Hooli.Lamp",Password="12345678";
void Task(void *p)
{
  for(;;)
  {
    mp3_play();
    Delay(15);
  }
}
void InitLamp()
{
  InitMatrix();
  ConfigFS();
  LoadData();
  WiFiStart();  
}


void setup()
{
  Serial.begin(115200);
  InitLamp();
  PlayAudio("/Startup.mp3");  
}


void loop()
{ 
  //PlayAudio("/Startup.mp3");
  Delay(30000);
}