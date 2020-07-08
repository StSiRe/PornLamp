long long unsigned int _secondsToWakeUp = 0;
#define uS_TO_S_FACTOR 1000000ULL
long long unsigned int SecondsToSleep(tm current,tm wakeUp)
{
    long long unsigned int Wake,Now;
    Wake = wakeUp.tm_mday*24*60*60 + wakeUp.tm_hour*60*60 + wakeUp.tm_min*60 + wakeUp.tm_sec;
    Now = current.tm_mday*24*60*60 + current.tm_hour*60*60 + current.tm_min*60 + current.tm_sec;
    return Wake - Now;    
}
void StartDeepSleep()
{
    esp_deep_sleep_start();
}
void InitDeepSleep()
{
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_14,1); //1 = High, 0 = Low
    Log.addLog("Going to deep sleep", "DeepSleep.h");
    SaveData();
    StopAnimations();
    OffMatrix();
    StartDeepSleep();
}
void InitDeepSleep(tm current,tm wakeTime)
{
    _secondsToWakeUp = SecondsToSleep(current,wakeTime);     
    esp_sleep_enable_timer_wakeup(_secondsToWakeUp * uS_TO_S_FACTOR);
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_14,1); //1 = High, 0 = Low
   Log.addLog("Going to deep sleep", "DeepSleep.h");
    StartDeepSleep();   
}
void InitDeepSleep(int seconds)
{
    _secondsToWakeUp = seconds; 
    esp_sleep_enable_timer_wakeup(_secondsToWakeUp * uS_TO_S_FACTOR);
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_14,1); //1 = High, 0 = Low
    Log.addLog("Going to deep sleep", "DeepSleep.h");
    StartDeepSleep();
}
