#include<Arduino.h>
#include<FreeRTOS.h>
#ifndef HooliButton_h
#define HooliButton_h

extern "C" {
typedef void (*callbackFunction)(void);
}



class  HooliButton
{
    public:
        HooliButton(int pin,bool pullup = false,bool isEnabledDebounce = false,int core = 0);

        void SetDebounceMS(int ms);

        //Устанавливает время для одного нажатия в последовательности
        void SetClickMS(int ms);

        //Устанавливает время после которого считается что кнопка зажата
        void SetPressMS(int ms);

        //Если распознано одиночное нажатие
        void AttachClick(callbackFunction Function);

        //Если распознано двойное нажатие
        void AttachDoubleClick(callbackFunction Function);

        //Если распознано тройное нажатие
        void AttachTripleClick(callbackFunction Function);

        //Срабатывает после прохода времени зажатия кнопки
        void AttachPressStartClick(callbackFunction Function);

        //Срабатывает при расжатии кнопки
        void AttachPressStopClick(callbackFunction Function);

        //Возращает время последнего удержания кнопки
        unsigned int GetPressedMS();

        void Tick();
    private:
        int ButtonPin;

        bool currentState = false;

        bool previousState = false;

        bool buttonHolded = false;

        unsigned int counter = 0;

        unsigned int debounceMS = 50;

        unsigned int clickMS = 150;

        unsigned int pressMS = 500;

        unsigned int pressStart = 0;

        unsigned int pressStop = 0;

        unsigned int pressTime = 0;

        bool isEnabledDebounce = false;

        callbackFunction clickFunc = NULL;

        callbackFunction doubleClickFunc = NULL;

        callbackFunction tripleClickFunc = NULL;

        callbackFunction pressStartFunc = NULL;

        callbackFunction pressStopFunc = NULL;
};  
#endif