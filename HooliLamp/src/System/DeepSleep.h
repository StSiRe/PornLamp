#include<time.h>

long long unsigned int _secondsToWakeUp = 0;
#define uS_TO_S 1000000

void InitDeepSleep(tm current,tm wakeTime)
{
    _secondsToWakeUp = SecondsToSleep(current,wakeTime); 
}

long long unsigned int SecondsToSleep(tm current,tm wakeUp)
{
    long long unsigned int Wake,Now,seconds;
    Wake = wakeUp.tm_mday*24*60*60 + wakeUp.tm_hour*60*60 + wakeUp.tm_min*60 + wakeUp.tm_sec;
    Now = current.tm_mday*24*60*60 + current.tm_hour*60*60 + current.tm_min*60 + current.tm_sec;
    return Wake - Now;    
}