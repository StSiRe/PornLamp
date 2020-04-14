#include<HooliButton.h>
#define ButtonPin 14

extern void Delay(int milliseconds);
extern void WriteLine(String text);

HooliButton button(ButtonPin);


extern String _currentAnimation;
extern String AnimationModes[];
extern int AnimationCount;
extern bool isAlarmWorking;
extern void StopAlarm();
extern void ChangeAnimation(String animationName);
void Click()
{
    Serial.println("Click");
    if(!isAlarmWorking)
    {
        int anim =0;
        for(int i=0;i < AnimationCount;i++)
        {
            if(_currentAnimation == AnimationModes[i])
            {
                anim = i;
            }
        }
        if((anim+1) == AnimationCount)
            anim = -1;
        ChangeAnimation(AnimationModes[anim+1]);
    }
    else
    {
        StopAlarm();
    }    
}


void DoubleClick()
{
    Serial.println("DoubleClick");
    ChangeAnimation("LampWhite");
}



extern void OffMatrix();
extern void OnMatrix();
bool powerState = false;
void TripleClick()
{
    Serial.println("TripleClick");
    powerState = !powerState;
    if(powerState)
    {        
        OffMatrix();
    }
    else
    {
        OnMatrix();
    }
}


extern int GetBrightness();
extern void SetBrightness(int brightness);
bool brighntnessWheel = false;
int lastCurr = 0;
void HoldStart()
{   
    Serial.println("HoldStart");
    int curr = button.GetPressedMS();
    Serial.println(curr);
    curr /= 250;
    Serial.println(curr);
    if(brighntnessWheel)
    {
        SetBrightness(GetBrightness() - curr);
    }
    else
    {
        SetBrightness(GetBrightness() + curr);
    }
    Serial.println(GetBrightness());
    lastCurr = curr;
}

void HoldEnd()
{
    Serial.print("HoldEnd: ");
    Serial.println(button.GetPressedMS());    
    brighntnessWheel = !brighntnessWheel;

}

void Tick(void *pv)
{
    for(;;)
    {
        button.Tick();
        Delay(15);//Возможно стоит уменьшить
    }
}
void InitButton()
{
    button.AttachClick(Click);
    button.AttachDoubleClick(DoubleClick);
    button.AttachTripleClick(TripleClick);
    button.AttachPressStartClick(HoldStart);
    button.AttachPressStopClick(HoldEnd);    
    xTaskCreatePinnedToCore(Tick,"HooliButton Tick",2048,NULL,1,NULL,1);
}