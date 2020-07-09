#include "HooliLog.h"
extern tm GetTime();

LogHandler::LogHandler(bool debugMode)
{
    _debug = debugMode;
    queueSize = 0;
    timeInfo = GetTime();
    start = Clock(millis());
}

void LogHandler::addLog(String action, String source, int state)
{
    if(queueSize == MAX_LOGS_COUNT)
    {
        logsList.pop();
        --queueSize;
    }
    
    Clock now(millis());
    logsList.push(LogNode(action, timeInfo.tm_hour + now.hour - start.hour, timeInfo.tm_min + now.minute 
    - start.minute, timeInfo.tm_sec + now.second - start.second, source, state));
    ++queueSize; 
    
    if(_debug)
    {
        logsList.back().print();
    }
}

void LogHandler::addLog(String action, int state)
{
    if(queueSize == MAX_LOGS_COUNT)
    {
        logsList.pop();
        --queueSize;
    }
    
    Clock now(millis());
    logsList.push(LogNode(action, timeInfo.tm_hour + now.hour - start.hour, timeInfo.tm_min + now.minute 
    - start.minute, timeInfo.tm_sec + now.second - start.second, "", state));
    ++queueSize;
    
    if(_debug)
    {
        logsList.back().print();
    }
}