
extern void InitDeepSleep();
extern int GetTimeout();
void TaskSWD(void *pvParametr);
xTaskHandle wdHandle;
//System WatchDog следит за памятью,и выводит ее состояние в консоль
void InitSystemWD()
{
    xTaskCreatePinnedToCore(TaskSWD,"WatchDog",8096,NULL,1,&wdHandle,0);
}

bool timeoutEnabled = true;
int timeoutCounterSleep = 0;
int timerSave = 0;
void TaskSWD(void *pvParametr)
{    
    for(;;)
    {
        Delay(10000);
        if(timeoutEnabled)
        timeoutCounterSleep+=10;
        timerSave+=10;
        uint32_t freeRam = ESP.getFreeHeap();
        WriteLine(ESP.getCpuFreqMHz());
        Write("Current ram free heap:");
        WriteLine(freeRam);
        
        WriteLine("Current time without upd:" + timerSave);
        if(timeoutCounterSleep > GetTimeout())
        {
            timeoutCounterSleep = 0;
            InitDeepSleep();
        }
        if(timerSave == 60)
        {
            timerSave = 0;
            SaveData();
        }
    }
    vTaskDelay(NULL);
}
void ClearTimeoutTimer()
{
    timeoutCounterSleep=0;
}
void PauseTimeoutTimer()
{
    timeoutEnabled=false;
}
void ResumeTimeoutTimer()
{
    timeoutEnabled=true;
}