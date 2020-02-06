#include<HTTPClient.h>//Нахуй не надо - но без него не работает аудио...
#include <Arduino.h>
#include<Audio/mp3.h>
#include<Functions.h>
#include<FileSystem/FileSys.h>
#include<Wifi/Wifi.h>
#include<Led/Display.h>
#include<Led/Animations.h>
#include<System/Time.h>
String Ssid="Hooli.Lamp",Password="12345678";
//String Ssid="521",Password="12345678";


//extern void WriteLine(String text);
//extern char* ToChar(String command);
//extern void ConfigFS();
//extern void WiFiStart();
//extern void initMatrix();

extern void LampOn();
extern void ChangeAnimation(String animationName);
void InitLamp()
{
  WriteLine("Hooli.Lamp is loading...");
  InitMatrix();
  InitAnimations();
  
  //LampOn();
  //ConfigFS();
  //LoadData();
  //WiFiStart();
  InitTime();
}
void setup()
{
  Serial.begin(115200);
  InitLamp();  
}


void loop()
{  
  ChangeAnimation("Fire");
  vTaskDelay(5000/portTICK_RATE_MS);
  ChangeAnimation("Rainbow");
  vTaskDelay(5000/portTICK_RATE_MS);
  ChangeAnimation("Hue");
  vTaskDelay(5000/portTICK_RATE_MS);
}
