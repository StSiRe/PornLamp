extern std::vector<AlarmClock> AlarmClocks;
extern void Delay(int milliseconds);
extern void WriteLine();
extern void Write();
extern void SaveData();
extern tm GetTime();
//Prototypes
void InitAlarmClock();
void CheckTimeForAlarmClock();
void AddAlarmClock(AlarmClock alarm);



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
}
void CheckTimeForAlarmClock()
{

}
void AddAlarmClock(AlarmClock alarm)
{
    WriteLine("Alarm Clock: Addinh new alarm clock");
    AlarmClocks.push_back(alarm);
    SaveData();
    WriteLine("Alarm Clock: All alarm clock`s saved");
}

