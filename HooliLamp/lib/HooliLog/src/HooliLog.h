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
    LogHandler(bool debugMode);
    
    void addLog(String action, String source, int state = 0);
    void addLog(String action, int state = 0);

private:
    std::queue<LogNode> logsList;
    unsigned int queueSize;
    
    bool _debug;
    
    // For time counting
    tm timeInfo;
    Clock start;
};

#endif