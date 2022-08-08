//#include <HTTPClient.h> //Нахуй не надо - но без него не работает аудио...
//#include <Arduino.h>

#include <HooliLog.h>
LogHandler Log(true);

#include "Functions.h"

#include "FileSystem/FileSys.h"
#include "FileSystem/Settings.h"

#include "Wifi/Wifi.h"

#include "Audio/Controller.h"

#include "Led/Display.h"
#include "Led/Animations.h"

#include "System/Time.h"
#include "System/Alarm/Dawn.h"
#include "System/Status.h"
#include "System/DeepSleep.h"
#include "System/Battery.h"

#include <Button/Button.h>

String Ssid="Hooli.Lamp",Password="12345678";

static int idle_cnt0 = 0;
static int idle_cnt1 = 0;
static void    idle_task0(void *parm)

{
    while(1==1)
        {
        int64_t now = esp_timer_get_time();     // time anchor
        vTaskDelay(0 / portTICK_RATE_MS);
        int64_t now2 = esp_timer_get_time();
        idle_cnt0 += (now2 - now) / 1000;        // diff
        }
}
static void    idle_task1(void *parm)

{
    while(1==1)
        {
        int64_t now = esp_timer_get_time();     // time anchor
        vTaskDelay(0 / portTICK_RATE_MS);
        int64_t now2 = esp_timer_get_time();
        idle_cnt1 += (now2 - now) / 1000;        // diff
        }
}
static void    mon_task(void *parm)
{
    while(1==1)
        {
        // Note the trick of saving it on entry, so print time
        // is not added to our timing.
        
        float new_cnt0 =  (float)idle_cnt0;    // Save the count for printing it ...
        float new_cnt1 =  (float)idle_cnt1;
        // Compensate for the 100 ms delay artifact: 900 ms = 100%
        float cpu_percent0 = ((99.9 / 90.) * new_cnt0) / 10;
        float cpu_percent1= ((99.9 / 90.) * new_cnt1) / 10;
        printf("C0:");
        printf("%.0f%%  ", 100 - cpu_percent0); fflush(stdout);
        printf(" C1:");
        printf("%.0f%%  ", 100 - cpu_percent1); fflush(stdout);
        printf("\n");
        idle_cnt0 = 0;      
        idle_cnt1 = 0;                      // Reset variable
        vTaskDelay(1000 / portTICK_RATE_MS);
        }
}
void InitLamp()
{  
  //xTaskCreatePinnedToCore(idle_task0, "idle_task0", 1024 * 2, NULL,  0, NULL,0);
  //xTaskCreatePinnedToCore(idle_task1, "idle_task1", 1024 * 2, NULL,  0, NULL,1);
  //xTaskCreate(mon_task, "mon_task", 1024 * 2, NULL, 10, NULL);

  InitMatrix();
  SetMaxBrightness(64);

  ConfigFS();
  LoadData();
  
  
  InitAnimations();

  InitWiFi();
  Delay(500);
  
  
  //SetBrightness(64);
  //InitTime();
  
  //InitAlarmClock();
  
  //InitSystemWD();

  //InitButton();
  
  InitBattery(true);
  SetBrightness(64);
  SetMaxBrightness(192);
  ChangeAnimation("Fire");
  SetupAudioDevice();
}



void setup()
{
  Serial.begin(115200);
  InitLamp();  
}


void loop()
{ 
  Delay(1000);
}

//ToDO Голубой ветерок! Лава И Змею!