#include<Esp.h>
#include<string.h>
extern void InitDeepSleep();
extern void WriteLine(String text);
extern void Delay(int milliseconds);
extern int GetTimeout();
void TaskSWD(void *pvParametr);
xTaskHandle wdHandle;
//System WatchDog следит за памятью,и выводит ее состояние в консоль
void InitSystemWD()
{
    xTaskCreatePinnedToCore(TaskSWD,"WatchDog",2048,NULL,1,&wdHandle,0);
}


long timeCounter = 0;
void TaskSWD(void *pvParametr)
{
    
    for(;;)
    {
        Delay(10000);
        timeCounter+=10000;
        uint32_t freeRam = ESP.getFreeHeap();
        WriteLine(String(freeRam));
        WriteLine("Current time without upd:" + timeCounter);
        if(timeCounter > GetTimeout() * 1000)
        {
            timeCounter = 0;
            InitDeepSleep();
        }
    }
    vTaskDelay(NULL);
}
void UpdateTimeTimer()
{
    timeCounter=0;
}