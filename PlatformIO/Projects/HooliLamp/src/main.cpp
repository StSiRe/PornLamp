#include<HTTPClient.h>//Нахуй не надо - но без него не работает аудио...
#include <Arduino.h>
#include<Audio/mp3.h>
#include<Functions.h>
#include<FileSystem/FileSys.h>
#include<Wifi/Wifi.h>
#include<Led/Display.h>
#include<Led/Animations.h>
//String Ssid="Hooli.Lamp",Password="12345678";
String Ssid="521",Password="intel5689";


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
  LampOn();
  ConfigFS();
  WiFiStart();



  ChangeAnimation("WiFiConnectionProcess");
  vTaskDelay(5000/portTICK_PERIOD_MS);
  ChangeAnimation("WiFiConnectionSuccess");
  vTaskDelay(5000/portTICK_PERIOD_MS);
  ChangeAnimation("WiFiConnectionProcess");
}


void loop()
{
}
