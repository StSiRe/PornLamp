#include <time.h>

#ifndef Time_h
#define Time_h

const char* ntpServer = "pool.ntp.org";

void printLocalTime()
{
  tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    WriteLine("Failed to obtain time");
    return;
  }
  if(Debug)
  {
    Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
  }
}
tm GetTime()
{
    tm timeinfo;
    if(!getLocalTime(&timeinfo)){
        WriteLine("Failed to obtain time");
        return timeinfo;
    }
    return timeinfo;
}

bool InitTime()
{
    if(!getWiFiConfigState())
    {
      WriteLine("WiFi not connected....");
      Log.addLog("Time can`t be install", "Time.h",-1);
      // WriteLine("WiFi not connected....");
      // WriteLine("Time can`t be install");
      return false;
    }
    configTime(3600*GetUTC(),0, ntpServer);
    WriteLine("NTP configurated.Updating time...");
    //WriteLine("NTP configurated.Updating time...");
    printLocalTime();
    Delay(10);
    Log.updateTime();
    Log.addLog("Time was configurated succesfuly", "Time.h",1);
    return true;
}
#endif