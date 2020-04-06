#include<HooliButton.h>
//#include<FreeRTOS.h>
HooliButton::HooliButton(int pin,bool pullup,bool isEnabledDebounce,int core)
{
    ButtonPin = pin;
    if(pullup)
    {
        pinMode(ButtonPin,INPUT_PULLUP);
    }        
    else
    {
        pinMode(ButtonPin,INPUT);
    }        
    HooliButton::isEnabledDebounce = isEnabledDebounce;
}
void HooliButton::Tick()
{
    currentState = digitalRead(ButtonPin);
    if(currentState == true && previousState == false)
    {
        previousState = currentState;
        pressStart = millis(); 
        buttonHolded = false;
    }
    if(currentState == true && (millis() - pressStart) > pressMS)
    {
        pressTime = millis() - pressStart;
        buttonHolded = true;
        if(pressStartFunc)
        {
            pressStartFunc();
        }
    }
    if((millis() - pressStop) > max(counter*clickMS,(unsigned)250))
    {
        if(!buttonHolded)
        {
            if(counter == 1)
            {        

                if(clickFunc)
                {
                    clickFunc();
                }                
            }
            if(counter == 2)
            {
                if(doubleClickFunc)
                {
                    doubleClickFunc();
                }                
            }
            if(counter == 3)
            {
                Serial.println("Trip");
                if(tripleClickFunc)
                {
                    tripleClickFunc();
                }                
            }
            
        }
        counter = 0;
    }
    if(currentState == false && previousState == true)
    {
        //Кнопка отпущена
        previousState = currentState;
        pressStop = millis();
        pressTime = pressStop - pressStart;//Общее время отпуска
        //if(pressTime < debounceMS)//Очен спорная хуйня,но делать нечего до 30 числа - Даже не купить новый датчик
        //    return;
        counter++;
        Serial.println("Button unholded");
        Serial.println(pressTime);
        //pressStart = 0;
        //pressStop = 0;
        if(pressTime > pressMS)
        {
            if(pressStopFunc)            
            {
                pressStopFunc();//Вызываем событие с  
            }
        }
    }    
}


void HooliButton::SetClickMS(int ms)
{
    clickMS = ms;
}
void HooliButton::SetDebounceMS(int ms)
{
    debounceMS = ms;
}
void HooliButton::SetPressMS(int ms)
{
    pressMS = ms;
}




void HooliButton::AttachClick(callbackFunction Function)
{
    clickFunc = Function;
}
void HooliButton::AttachDoubleClick(callbackFunction Function)
{
    doubleClickFunc = Function;
}
void HooliButton::AttachTripleClick(callbackFunction Function)
{
    tripleClickFunc = Function;
}
void HooliButton::AttachPressStartClick(callbackFunction Function)
{
    pressStartFunc = Function;
}
void HooliButton::AttachPressStopClick(callbackFunction Function)
{
    pressStopFunc = Function;
}

unsigned int HooliButton::GetPressedMS()
{
    return pressTime;
}

