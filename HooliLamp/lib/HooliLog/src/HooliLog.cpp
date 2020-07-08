#include "HooliLog.h"
extern tm GetTime();

LogHandler::LogHandler(bool debugMode)
{
    _debug = debugMode;
}

void LogHandler::addLog(String action, String source, int state)
{
    if(logsList.size() == MAX_LOGS_COUNT)
    {
        logsList.pop();
    }
    tm timeInfo = GetTime();
    logsList.push(LogNode(action,timeInfo.tm_hour,timeInfo.tm_min,timeInfo.tm_sec, source, state));
    if(_debug)
    {
        logsList.back().print();
    }
}

void LogHandler::addLog(String action, int state)
{
    if(logsList.size() == MAX_LOGS_COUNT)
    {
        logsList.pop();
    }
    tm timeInfo = GetTime();
    logsList.push(LogNode(action,timeInfo.tm_hour,timeInfo.tm_min,timeInfo.tm_sec, "", state));
    if(_debug)
    {
        logsList.back().print();
    }
}