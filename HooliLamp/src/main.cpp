#include<HTTPClient.h>//Нахуй не надо - но без него не работает аудио...
#include<Arduino.h>
#include<Functions.h>
#include<FileSystem/FileSys.h>
#include<Wifi/Wifi.h>
#include<Led/Display.h>
#include<Led/Fire.h>
<<<<<<< HEAD
#include<Audio/Controller.h>
=======
#include<Led/Rainbow.h>
#include<Led/MatrixAnimation.h>
>>>>>>> ebdb1f1b4cc99b22909cdb03745cbd71b026add2

String Ssid="Hooli.Lamp",Password="12345678";
void Task(void *p)
{
  for(;;)
  {
<<<<<<< HEAD
    mp3_play();
    Delay(15);
=======
    //Fire();
    MatrixRoutine();
>>>>>>> ebdb1f1b4cc99b22909cdb03745cbd71b026add2
  }
}
void InitLamp()
{
  InitMatrix();
  ConfigFS();
  LoadData();
<<<<<<< HEAD
  WiFiStart();  
=======
  WiFiStart();
  delay(100);
  xTaskCreatePinnedToCore(Task,"ta",8192,NULL,3,NULL,1);
>>>>>>> ebdb1f1b4cc99b22909cdb03745cbd71b026add2
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