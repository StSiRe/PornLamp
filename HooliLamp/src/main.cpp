#include<HTTPClient.h>//Нахуй не надо - но без него не работает аудио...
#include<Arduino.h>
#include<Functions.h>
#include<FileSystem/FileSys.h>
#include<Wifi/Wifi.h>
#include<Led/Display.h>
#include<Led/Fire.h>

String Ssid="Hooli.Lamp",Password="12345678";
void Task(void *p)
{
  for(;;)
  {    
    Fire();
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
}


void loop()
{
  delay(10);
}