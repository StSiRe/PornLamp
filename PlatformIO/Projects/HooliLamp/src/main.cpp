#include<HTTPClient.h>//Нахуй не надо - но без него не работает аудио...
#include <Arduino.h>
#include<Audio/mp3.h>
#include<Functions.h>
#include<FileSystem/FileSys.h>
#include<FileSystem/Settings.h>
#include<Wifi/Wifi.h>

String Ssid="Hooli.Lamp",Password="12345678";


extern void WriteLine(String text);
extern char* ToChar(String command);
extern void ConfigFS();
extern void WiFiStart();

void setup()
{
  Serial.begin(115200);
  WriteLine("Hooli.Lamp is loading...");
  ConfigFS();
  WiFiStart();
}


void loop()
{

}
