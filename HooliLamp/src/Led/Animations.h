#include<Led/Fire.h>
#include<Led/SystemAnimations.h>
#include<Led/Rainbow.h>
#include<Led/Sparks.h>
#include<Led/MatrixAnimation.h>
#include<Led/Firework.h>

#include<string.h>
extern const int Height;
extern const int Width;
extern int XY(int x,int y);

extern void ClearTimeoutTimer();
extern void WriteLine(String text);
extern void Delay(int milliseconds);
extern void SetBrightness(int brightness);
extern int GetBrightness();

bool _updateReqied = false;

String _currentAnimation = "";
String _previosAnimation = "";
int currentAnimationNum =  10;
xTaskHandle Animation;
int AnimationCount =5;
String AnimationModes[]  = {
    "Fire",
    "Rainbow",
    "RainbowH",
    "Matrix",
    "Sparks",
    "Firework",
    "LampWhite"
};
void TaskAnimation(void *pvParameter)
{
    for (;;)
    {
        if(_updateReqied)
        {
            _updateReqied=false;
            ClearMatrix();
            strip.Show();
        }
        if(_currentAnimation == "WiFiConnectionProcess")
        {
            WiFiConnectionProcess();
        }
        else if(_currentAnimation == "WiFiConnectionSuccess")
        {
            WiFiConnectionSuccess();       
        }
        else if(_currentAnimation == "LampOn")
        {
            LampOn();
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
            Hue();
        }        
        else if(_currentAnimation == "Sparks" || currentAnimationNum == 3)
        {
            Sparks();
        } 
        else if(_currentAnimation == "Matrix" || currentAnimationNum == 4)
        {
            MatrixRoutine();
        }
        else if(_currentAnimation == "RainbowH" || currentAnimationNum == 5)
        {
            RainbowH();
        }
        else if(_currentAnimation == "Penis" || currentAnimationNum == 6)
        {
            Penis();
        }
        else if(_currentAnimation == "Firework" || currentAnimationNum == 7)
        {
            Firework();
        }
        else if(_currentAnimation == "LampWhite")
        {
            for(int i =0;i < 256;i++)
            {
                strip.SetPixelColor(i,RgbColor(255,255,255));
            }
            strip.Show();
            Delay(50);
        }
        else
        {
            LampOn();
        }
        Delay(1);
    }
    vTaskDelete(NULL);
}
//Сменить анимацию по имени
void ChangeAnimation(String animationName)
{
    WriteLine("Changing Animation to: " + animationName);
    _previosAnimation = _currentAnimation;
    _currentAnimation=animationName;
    _updateReqied = true;
    //SetBrightness(64);
    ClearTimeoutTimer();
}

//Инициализирует и запускает поток для анимаций
//Использовать перед ChangeAnimation!
void InitAnimations()
{
    WriteLine("Animations is initializing....");
    xTaskCreatePinnedToCore(TaskAnimation,"Animation",8192,NULL,100,&Animation,1);
    WriteLine("Animation Task was initializated.");
}

//Удаляет поток анимаций.После этого требуется заново проинициализировать анимации
void StopAnimations()
{
    if(Animation!= NULL)
    {        
        WriteLine("Warning: Stopping animations");
        vTaskDelete(Animation);
    }
}
