#include<HTTPClient.h>//Нахуй не надо - но без него не работает аудио...
#include<Arduino.h>
#include<Functions.h>
#include<FileSystem/FileSys.h>
#include<Wifi/Wifi.h>
#include<Led/Display.h>
#include<Audio/Controller.h>
#include<System/Time.h>
#include<Led/Sparks.h>

String Ssid="Hooli.Lamp",Password="12345678";
void Task(void *p)
{
  for(;;)
  {
   //mp3_play();
    //Fire();
    Sparks();
  }
}
void InitLamp()
{
  InitMatrix();
  ConfigFS();
  LoadData();
  WiFiStart();
  
  xTaskCreatePinnedToCore(Task,"ta",8192,NULL,3,NULL,1);
}


void setup()
{
  Serial.begin(115200);
  InitLamp();
  PlayAudio("/Sound/Notification.mp3");  
}


void loop()
{ 
  //PlayAudio("/Startup.mp3");
  Delay(30000);
}