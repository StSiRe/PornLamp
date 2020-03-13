#include<HTTPClient.h>//Нахуй не надо - но без него не работает аудио...
#include<Arduino.h>
#include<Functions.h>
#include<FileSystem/FileSys.h>
#include<Wifi/Wifi.h>
#include<Led/Display.h>
#include<Audio/Controller.h>
<<<<<<< HEAD
#include<Led/Animations.h>

String Ssid="Hooli.Lamp",Password="12345678";

=======
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
>>>>>>> 667c0d8869e8a45e2cfcaa7e703ec187898ccdeb
void InitLamp()
{
  InitMatrix();
  ConfigFS();
  LoadData();
  WiFiStart();
<<<<<<< HEAD
  InitAnimations();
=======
  
  xTaskCreatePinnedToCore(Task,"ta",8192,NULL,3,NULL,1);
>>>>>>> 667c0d8869e8a45e2cfcaa7e703ec187898ccdeb
}


void setup()
{
  Serial.begin(115200);
  InitLamp();
<<<<<<< HEAD
  //PlayAudio("/Startup.mp3");  
  Delay(1000);
=======
  PlayAudio("/Sound/Notification.mp3");  
>>>>>>> 667c0d8869e8a45e2cfcaa7e703ec187898ccdeb
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