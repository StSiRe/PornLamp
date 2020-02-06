#include<time.h>

long _secondsToWakeUp = 0;
#define uS_TO_S 1000000

void InitDeepSleep(tm current,tm wakeTime)
{
    _secondsToWakeUp = SecondsToSleep(current,wakeTime); 
}

long SecondsToSleep(tm current,tm wakeUp)
{
    int year = wakeUp.tm_year - current.tm_year;
    int month = wakeUp.tm_mon - current.tm_mon;
    int day = wakeUp.tm_mday - current.tm_mday;
    int hour = wakeUp.tm_hour - current.tm_hour;
    int min = wakeUp.tm_min - current.tm_min;
    int seconds = wakeUp.tm_sec - current.tm_sec;
    if(year >= 0)
    {
        if(month>=0)
        {
            if(day>=0)
            {
                if(hour>=0)
                {
                    if(min>=0)
                    {
                        if(seconds>=0)
                        {
                            
                        }
                    }
                }
            }
        }
    }
}