#include<HTTPClient.h>//Нахуй не надо - но без него не работает аудио...
#include <Arduino.h>
#include<Audio/mp3.h>
#include<Functions.h>
#include<FileSystem/FileSys.h>
#include<Wifi/Wifi.h>
#include<Led/Display.h>
#include<Led/Animations.h>
String Ssid="Hooli.Lamp",Password="12345678";
//String Ssid="521",Password="12345678";


extern void WriteLine(String text);
extern char* ToChar(String command);
extern void ConfigFS();
extern void WiFiStart();
extern void initMatrix();

extern void LampOn();
extern void ChangeAnimation(String animationName);

void setup()
{
  Serial.begin(115200);
  WriteLine("Hooli.Lamp is loading...");
  initMatrix();
  //LampOn();
  //ConfigFS();
  //WiFiStart();
  ChangeAnimation("Sparks");
  vTaskDelay(10000/portTICK_RATE_MS);
  ChangeAnimation("Fire");
  vTaskDelay(10000/portTICK_RATE_MS);
  ChangeAnimation("Rainbow");
  vTaskDelay(10000/portTICK_RATE_MS);
  ChangeAnimation("Hue");
  vTaskDelay(10000/portTICK_RATE_MS);
}


void loop()
{  
  /*
  ChangeAnimation("Sparks");
  delay(5000);
  ChangeAnimation("Fire");
  delay(5000);
  ChangeAnimation("Rainbow");
  delay(5000);
  ChangeAnimation("Hue");
  delay(5000);*/
  while(true){
    FastLED.clear();
    FastLED.clearData();
  ChangeAnimation("WiFiConnectionSuccess");
  delay(5000);
  ChangeAnimation("WiFiConnectionProcess");
  delay(5000);}
}
