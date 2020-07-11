#include <Arduino.h>

struct Clock
{
    Clock(int h, int m, int s) : hour(h), minute(m), second(s){}
    Clock(){}
    Clock(unsigned long ms) // заполняет структуру секунд, минут и часов, принимая значение в мс
    {
        hour = (ms / (1000*60*60)) % 24;
        ms = ms % (1000*60*60);
        minute = ms / (1000*60);
        ms = ms % (1000*60);
        second = ms / (1000);
    }
    int hour;
    int minute;
    int second;
};

struct LogNode
{
    LogNode(String a, int h, int m, int s, String so, int st)
    {
        action = a;
        cl.hour = h;
        cl.minute = m;
        cl.second = s;
        source = so;
        state = st;
    }
    
    void print()
    {
        if(source != "") // случай указанного источника
        {
            source += ": "; 
        }
        String answer = (String)cl.hour + ':' + (String)cl.minute + ':' + (String)cl.second + ' ' + source + action;
        if(state > 0) // случай указания результата 
        {
            answer += " [✓]";
        } else if(state < 0) {
            answer += " [x]";
        }
        Serial.println(answer); 
    }
    
    String action; // событие для лога
    Clock cl; // структура времени
    String source; // источник событя
    int state; // результат события: -1 - [х]   |   0 - нейтр.  |   1 - [✓]
    
};