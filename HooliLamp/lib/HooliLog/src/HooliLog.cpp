#include "HooliLog.h"
extern tm GetTime();

LogHandler::LogHandler(bool debugMode)
{
    _debug = debugMode;
    queueSize = 0;
    
    updateTime();
}

void LogHandler::addLog(String action, String source, int state)
{
    if(queueSize == MAX_LOGS_COUNT) // проверка на кол-во логов и удаление последнего при переполнении
    {
        logsList.pop();
        --queueSize;
    }
    
    Clock now(millis() + timeOffset); // расчет времени с учетом добавочного значения
    logsList.push(LogNode(action, now.hour, now.minute, now.second, source, state)); //добавление лога с источником
    ++queueSize; 
    
    if(_debug)
    {
        logsList.back().print(); //вывод добавленного элемента
    }
}

void LogHandler::addLog(String action, int state)
{
    if(queueSize == MAX_LOGS_COUNT) // проверка на кол-во логов и удаление последнего при переполнении
    {
        logsList.pop();
        --queueSize;
    }
    
    Clock now(millis() + timeOffset);// расчет времени с учетом добавочного значения
    logsList.push(LogNode(action, now.hour, now.minute, now.second, "", state)); //добавление лога без источника
    ++queueSize;
    
    if(_debug)
    {
        logsList.back().print(); //вывод добавленного элемента
    }
}

void LogHandler::updateTime()
{
    tm timeInfo;
    timeInfo = GetTime(); //считывание времени через класс Time.h
    timeOffset = ((timeInfo.tm_hour * 60 + timeInfo.tm_min) * 60 + timeInfo.tm_sec) * 1000; //добавочное значение в миллисекундах 
}