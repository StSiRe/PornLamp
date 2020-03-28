#include<Arduino.h>
#ifndef HooliButton_h
#define HooliButton_h

extern "C" {
typedef void (*callbackFunction)(void);
typedef void (*parameterizedCallbackFunction)(void*);
}



class  HooliButton
{
    public:
        HooliButton(int pin,bool isEnabledDebounce = false);

        void SetDebounceMS(int ms);

        void SetClickMS(int ms);

        void SetPressMS(int ms);

        void DetachButton();

        void AttachClick(callbackFunction newFunction);

        void AttachDoubleClick(callbackFunction newFunction);

        bool isLongPressed();// - experemental

        int GetPressedMS();
    private:
        int ButtonPin;

        unsigned int debounceMS = 50;

        unsigned int clickMS = 500;
        
        unsigned int longPressMS = 1000;



};  
#endif