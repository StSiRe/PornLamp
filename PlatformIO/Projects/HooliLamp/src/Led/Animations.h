#include<FastLED.h>


#include<Led/Fire.h>
#include<Led/SystemAnimations.h>
#include<Led/Rainbow.h>
#include<Led/Sparks.h>
#include<Led/MatrixAnimation.h>

#include<string.h>
//extern CRGB leds_plus_safety_pixel[];
extern CRGB* const leds;
extern const int Height;
extern const int Width;
extern int XY(int x,int y);
extern void fireRoutine();
extern void LampOn();
extern void LampOff();
extern void WiFiConnectionProcess();
extern void WiFiConnectionSuccess();
extern void WriteLine(String text);
extern void Delay(int milliseconds);
bool _updateReqied = false;


String _currentAnimation = "";
int currentAnimationNum =  10;
xTaskHandle Animation;
String AnimationModes[]  = {
    "LampOn",
    "LampOff",
    "WiFiConnectionProcess",
    "WiFiConnectionSuccess",
    "Fire",
    "Rainbow"
    "MatrixAnimation"
};






void TaskAnimation(void *pvParameter)
{
    for (;;)
    {
        if(_updateReqied)
        {
            _updateReqied=false;
            FastLED.clear();
            FastLED.show();
        }
        if(_currentAnimation == "WiFiConnectionProcess")
        {
            WiFiConnectionProcess();
        }
        else if(_currentAnimation == "WiFiConnectionSuccess")
        {
            WiFiConnectionSuccess();       
        }
        else if(_currentAnimation == "Fire" || currentAnimationNum == 0)
        {
            Fire();
            
        }        
        else if(_currentAnimation == "Rainbow" || currentAnimationNum == 1)
        {
            RainbowV();
        }
        else if(_currentAnimation == "Hue" || currentAnimationNum == 2)
        {
            HueAnimation();
        }        
        else if(_currentAnimation == "Sparks" || currentAnimationNum == 3)
        {
            Sparks();
        } 
        else if(_currentAnimation == "MatrixAnimation")
        {
            matrixRoutine();
        }
        /*
        else if(_currentAnimation == "")
        {

        }*/
        else
        {
            Fire();
        }
        Delay(1);
    }
    vTaskDelete(NULL);
}

/*
int strAnim2Num(String name)
{
    for (size_t i = 0; i < sizeof(AnimationModes)/sizeof(AnimationModes[0]); i++)
    {
        if(AnimationModes[i] == name) return sizeof(AnimationModes)/sizeof(AnimationModes[0]) - i;
    }
    return -1;
}*/

//Сменить анимацию по имени
void ChangeAnimation(String animationName)
{
    WriteLine("Changing Animation to: " + animationName);
    _currentAnimation=animationName;
    _updateReqied=true;
    //currentAnimationNum = strAnim2Num(animationName);
}
//Инициализирует и запускает поток для анимаций
//Использовать перед ChangeAnimation!
void InitAnimations()
{
    WriteLine("Animations is initializing....");
    xTaskCreatePinnedToCore(TaskAnimation,"Animation",8192,NULL,100,&Animation,1);
    WriteLine("Animation Task was initializated.");
}

