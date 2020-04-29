#include<System/Alarm/TimeConverter.h>
extern std::vector<AlarmClock> AlarmClocks;
extern void Delay(int milliseconds);
extern void WriteLine();
extern void Write();
extern void SaveData();
extern tm GetTime();
extern bool sunrise(byte step);
extern void SetBrightness(int brightness);
extern int GetBrightness();
extern void StopAnimations();
extern void InitAnimations();
extern void PlayAudio(String name);
extern void StopAudio();
extern void PauseTimeoutTimer();
extern void ResumeTimeoutTimer();
void InitAlarmClock();
void CheckTimeForAlarmClock(void *pc);
void AddAlarmClock(AlarmClock alarm);
//Поток будильников
xTaskHandle AlarmClockTask;
//Работает ли сейчас будильник
bool isAlarmWorking = false;
void StopAlarm();

void Sunrise(tm current,AlarmClock alarm);
void InitAlarmClock()
{
    Serial.println("Initializating Alarm Clock");
    Serial.print("Alarm Clock count:");    
    int alarms = AlarmClocks.size();
    Serial.println(alarms);

    if(alarms == 0) return;

    Serial.println("Loaded Alarm Clocks:");
    for(int i = 0;i < alarms; i++)
    {
        Serial.print("Alarm Clock №");
        Serial.println(i);

        Serial.print("Time: ");
        Serial.print(AlarmClocks[i].Hour);
        Serial.print(":");
        Serial.println(AlarmClocks[i].Minute);

        Serial.print("Enabled: ");
        Serial.println(AlarmClocks[i].Enabled);

        Serial.print("Repeat: ");
        Serial.println(AlarmClocks[i].Repeat);

        Serial.print("Music: ");
        Serial.println(AlarmClocks[i].Music);

        Serial.print("Days: ");
        for(int j = 0;j < AlarmClocks[i].Days.size(); j++)
        {
            Serial.print(AlarmClocks[i].Days[j]);
            Serial.print("; ");
        }
        Serial.println("");
    }
    Serial.println("Alarm Clock: End of loaded alarm clocks");
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
            Serial.print("Clock #");
            Serial.println(i);
            AlarmClock alarm = AlarmClocks[i];
            if(alarm.Enabled)//Проверяем,активирован ли он
            {
                for(int j = 0; j < alarm.Days.size(); j++)
                {
                    int day = ConvertDayToInt(alarm.Days[j]);
                    Serial.println("Day:");
                    Serial.println(day);
                    Serial.println(time.tm_wday);
                    if(time.tm_wday == day || day == 7)//Если день совпадает
                    {
                        int hm = time.tm_hour*60 + time.tm_min - alarm.Hour* 60 - alarm.Minute;
                        Serial.println("HM: ");
                        Serial.println(hm);
                        if(hm > 0)//Если текущее время больше чем назначенное,то выходим
                            break;
                        hm = -hm;
                        int freeTime = hm - alarm.Sunrise;
                        Serial.println("FreeTime: ");
                        Serial.println(freeTime);
                        if(freeTime > 0)
                            break;

                        //Вот здесь и начнется рассвет
                        Serial.println("Sunrise!!!!!");
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

    while(!sunrise(5))// Приводим экран к необходимому цвету
    {
        Delay(100);
    }
    //Теперь начинается алгоритм поднятия яркости
    int timeToAlarm = alarm.Hour* 60 - alarm.Minute - current.tm_hour*60 - current.tm_min;//Оставшиеся время до рассвета
    int changeBrt = GetMaxBrightness() - GetBrightness();
    int delayTime = timeToAlarm/2*60 /*time to alarm in seconds*/;//Половина времни до рассвета в секудах
    int brightnessStep =  delayTime / changeBrt;// Изменение яркости за секунду
    Serial.println(brightnessStep);
    int timeCounter = 0;
    Serial.println(delayTime);
    for(int timeCounter =0;timeCounter < delayTime;timeCounter++)
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
    Serial.println("Stopping AlarmClock");
    if(AlarmClockTask)
    {
        vTaskDelete(AlarmClockTask);
        Delay(500);
    }        
    xTaskCreatePinnedToCore(CheckTimeForAlarmClock,"AlarmClock",2048,NULL,1,&AlarmClockTask,0);
}

