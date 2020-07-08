#include<System/Alarm/TimeConverter.h>
extern std::vector<AlarmClock> AlarmClocks;
extern void PauseTimeoutTimer();
extern void ResumeTimeoutTimer();
void CheckTimeForAlarmClock(void *pc);
//Поток будильников
xTaskHandle AlarmClockTask;
//Работает ли сейчас будильник
bool isAlarmWorking = false;

void Sunrise(tm current,AlarmClock alarm);
void InitAlarmClock()
{
    WriteLine("Initializating Alarm Clock");
    Write("Alarm Clock count:");    
    int alarms = AlarmClocks.size();
    WriteLine(alarms);

    if(alarms == 0) return;

    WriteLine("Loaded Alarm Clocks:");
    for(int i = 0;i < alarms; i++)
    {
        Write("Alarm Clock №");
        WriteLine(i);

        Write("Time: ");
        Write(AlarmClocks[i].Hour);
        Write(":");
        WriteLine(AlarmClocks[i].Minute);

        Write("Enabled: ");
        WriteLine(AlarmClocks[i].Enabled);

        Write("Repeat: ");
        WriteLine(AlarmClocks[i].Repeat);

        Write("Music: ");
        WriteLine(AlarmClocks[i].Music);

        Write("Days: ");
        for(int j = 0;j < AlarmClocks[i].Days.size(); j++)
        {
            Write(AlarmClocks[i].Days[j]);
            Write("; ");
        }
        WriteLine("");
    }
    WriteLine("Alarm Clock: End of loaded alarm clocks");
    Log.addLog("Alarm Clock initialized", "Dawn.h");
    xTaskCreatePinnedToCore(CheckTimeForAlarmClock,"AlarmClock",2048,NULL,1,&AlarmClockTask,0);
}
void CheckTimeForAlarmClock(void *pc)
{
    Delay(10000);//Небольшая задержка для стабильности
    while(true)
    {
        tm time = GetTime();
        for(int i = 0;i < AlarmClocks.size(); i++)
        {
            Write("Clock #");
            WriteLine(i);
            AlarmClock alarm = AlarmClocks[i];
            if(alarm.Enabled)//Проверяем,активирован ли он
            {
                for(int j = 0; j < alarm.Days.size(); j++)
                {
                    int day = ConvertDayToInt(alarm.Days[j]);
                    WriteLine("Day:");
                    WriteLine(day);
                    WriteLine(time.tm_wday);
                    if(time.tm_wday == day || day == 7)//Если день совпадает
                    {
                        int hm = time.tm_hour*60 + time.tm_min - alarm.Hour* 60 - alarm.Minute;
                        WriteLine("HM: ");
                        WriteLine(hm);
                        if(hm > 0)//Если текущее время больше чем назначенное,то выходим
                            break;
                        hm = -hm;
                        int freeTime = hm - alarm.Sunrise;
                        WriteLine("FreeTime: ");
                        WriteLine(freeTime);
                        if(freeTime > 0)
                            break;

                        //Вот здесь и начнется рассвет
                        WriteLine("Sunrise!!!!!");
                        if(!alarm.Used)
                        {
                            AlarmClocks[i].Used = true;
                            Sunrise(time,alarm);
                        }
                    }
                }
            }
        }
        Delay(30*1000);//30s
    }
}
void Sunrise(tm current,AlarmClock alarm)
{
    isAlarmWorking=true;
    PauseTimeoutTimer();
    Delay(10000); // Делаем задержку для стабильности
    StopAnimations();// Останавилваем отрисовку анимаций
    Log.addLog("AlarmClock started", "Dawn.h");
    while(!sunrise(5))// Приводим экран к необходимому цвету
    {
        Delay(100);
    }
    //Теперь начинается алгоритм поднятия яркости
    int timeToAlarm = alarm.Hour* 60 - alarm.Minute - current.tm_hour*60 - current.tm_min;//Оставшиеся время до рассвета
    int changeBrt = GetMaxBrightness() - GetBrightness();
    int delayTime = timeToAlarm/2*60 /*time to alarm in seconds*/;//Половина времни до рассвета в секудах
    int brightnessStep =  delayTime / changeBrt;// Изменение яркости за секунду
    WriteLine(brightnessStep);
    WriteLine(delayTime);
    for(int timeCounter = 0; timeCounter < delayTime; timeCounter++)
    {
        Delay(1000);
        SetBrightness(GetBrightness() + brightnessStep);
    }
    Delay(delayTime*1000);//Ждем оставшиеся время
    //PlayAudio(alarm.Music);
    Delay(10000);
    InitAnimations();
    isAlarmWorking=false;
    ResumeTimeoutTimer();
}
void AddAlarmClock(AlarmClock alarm)
{
    AlarmClocks.push_back(alarm);
    SaveData();//Сохраняем для безопасности данных
}
void StopAlarm()
{
    Log.addLog("AlarmClock stopped", "Dawn.h");
    if(AlarmClockTask)
    {
        vTaskDelete(AlarmClockTask);
        Delay(500);
    }        
    xTaskCreatePinnedToCore(CheckTimeForAlarmClock,"AlarmClock",2048,NULL,1,&AlarmClockTask,0);
}

