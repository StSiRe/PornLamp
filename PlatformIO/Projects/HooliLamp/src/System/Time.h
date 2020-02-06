#include <time.h>

extern int GetUTC();

const char* ntpServer = "pool.ntp.org";

extern void Delay(int milliseconds);
extern bool getWiFiConfigState();

void printLocalTime()
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    WriteLine("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}
tm GetTime()
{
    struct tm timeinfo;
    if(!getLocalTime(&timeinfo)){
        WriteLine("Failed to obtain time");
        return;
    }
    return timeinfo;
}

bool InitTime()
{
    if(!getWiFiConfigState)
    {
        WriteLine("WiFi not connected....");
        WriteLine("Time can`t be install");
        return false;
    }
    configTime(3600*GetUTC(),3600*GetUTC(), ntpServer);
    WriteLine("NTP configurated.Updating time...");
    printLocalTime();
    Delay(10);
}