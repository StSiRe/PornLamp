#include<HTTPClient.h>//Нахуй не надо - но без него не работает аудио...
#include<Arduino.h>
#include<Functions.h>
#include<FileSystem/FileSys.h>
#include<Wifi/Wifi.h>
#include<Led/Display.h>
<<<<<<< HEAD
#include<Led/Fire.h>

=======
#include<Led/Rainbow.h>
#include<Audio/mp3.h>
>>>>>>> 7f0fb98841331e7954409bf1fc3b71fe15e2d87a
String Ssid="Hooli.Lamp",Password="12345678";
void Task(void *p)
{
  for(;;)
  {    
<<<<<<< HEAD
    Fire();
=======
    RainbowV(); 
>>>>>>> 7f0fb98841331e7954409bf1fc3b71fe15e2d87a
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
  mp3_setup("Sound/Startup.mp3");
  mp3_play();
}


void loop()
{
  delay(10);
}