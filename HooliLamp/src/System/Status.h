#include<Esp.h>
#include<string.h>
extern void InitDeepSleep();
extern void WriteLine(String text);
extern void Delay(int milliseconds);
extern int GetTimeout();
void TaskSWD(void *pvParametr);
xTaskHandle wdHandle;
extern void SaveData();
//System WatchDog следит за памятью,и выводит ее состояние в консоль
void InitSystemWD()
{
    xTaskCreatePinnedToCore(TaskSWD,"WatchDog",8096,NULL,1,&wdHandle,0);
}


int timeCounterSleep = 0;
int timeCounterSave = 0;
void TaskSWD(void *pvParametr)
{
    
    for(;;)
    {
        Delay(10000);
        timeCounterSleep+=10000;
        timeCounterSave+=10;
        uint32_t freeRam = ESP.getFreeHeap();
        WriteLine(String(freeRam));
        WriteLine("Current time without upd:" + timeCounterSleep);
        if(timeCounterSleep > GetTimeout() * 1000)
        {
            timeCounterSleep = 0;
            InitDeepSleep();
        }
        if(timeCounterSave == 60)
        {
            timeCounterSave = 0;
            SaveData();
        }
    }
    vTaskDelay(NULL);
}
void UpdateTimeTimer()
{
    timeCounterSleep=0;
}