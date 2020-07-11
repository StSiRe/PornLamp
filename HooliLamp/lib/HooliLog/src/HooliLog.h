#include <Arduino.h>
#include <queue>
#include "Structures.h"

#ifndef HooliLog_h
#define HooliLog_h

#define MAX_LOGS_COUNT 50

class LogHandler
{
    friend void LogNode::print();
public:
    LogHandler(bool debugMode); // ctor с возможностью запрета печати 
    
    void addLog(String action, String source, int state = 0);
    void addLog(String action, int state = 0);

    void updateTime(); // синхронизация времени ESP и библиотеки

private:
    std::queue<LogNode> logsList; // очередь логов
    unsigned int queueSize; // подсчет кол-ва логов
    
    bool _debug;
    
    // For time counting
    unsigned long timeOffset; // добавочное значение 
};

#endif