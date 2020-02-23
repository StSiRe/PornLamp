#include<Esp.h>
#include<string.h>
extern void WriteLine(String text);
extern void Delay(int milliseconds);
void TaskSWD(void *pvParametr);
xTaskHandle wdHandle;
//System WatchDog следит за памятью,и выводит ее состояние в консоль
void InitSystemWD()
{
    xTaskCreatePinnedToCore(TaskSWD,"WatchDog",2048,NULL,1,&wdHandle,0);
}
void TaskSWD(void *pvParametr)
{
    for(;;)
    {
        Delay(10000);
        uint32_t freeRam = ESP.getFreeHeap();
        WriteLine(String(freeRam));
    }
    vTaskDelay(NULL);
}