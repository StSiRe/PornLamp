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
  //InitTime();
}
void setup()
{
  Serial.begin(115200);
  InitLamp();  

  
  /*SetBrightness(255);
  for(int i=0;i<256;i++)
  {
    leds[i] = CRGB(255,255,170);
  }
  FastLED.show();
  Delay(10000);*/
}


void loop()
{  
  ChangeAnimation("MatrixAnimation");
  Delay(5000);
  ChangeAnimation("Fire");Delay(5000);
  ChangeAnimation("Rainbow");Delay(5000);
  ChangeAnimation("Hue");Delay(5000);
}
