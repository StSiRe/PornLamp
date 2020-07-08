#include <Arduino.h>
#include <queue>

#ifndef HooliLog_h
#define HooliLog_h

#define MAX_LOGS_COUNT 50
using namespace std;



struct LogNode
{
    LogNode(String a, int h, int m, int s, String so, int st) : action(a), hour(h), minute(m), second(s), source(so), state(st){}
    void print()
    {
        if(source != "") 
        {
            source += ": ";
        }
        String answer = (String)hour + ':' + (String)minute + ':' + (String)second + ' ' + source + action;
        if(state > 0)
        {
            answer += " [✓]";
        } else if(state < 0) {
            answer += " [x]";
        }
        Serial.println(answer); 
    }
    
    String action;
    int hour;
    int minute;
    int second;
    String source;
    int state;
    
};

class LogHandler
{
    friend void LogNode::print();
public:
    LogHandler(bool debugMode);
    
    void addLog(String action, String source, int state = 0);
    void addLog(String action, int state = 0);

private:
    queue<LogNode> logsList;
    bool _debug;
};

#endif