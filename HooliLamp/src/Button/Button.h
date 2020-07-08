#include<HooliButton.h>
#define ButtonPin 25


HooliButton button(ButtonPin);

void Click()
{
    WriteLine("Click");
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
    WriteLine("DoubleClick");
    ChangeAnimation("LampWhite");
}



extern void OffMatrix();
extern void OnMatrix();
bool powerState = false;
void TripleClick()
{
    WriteLine("TripleClick");
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
    WriteLine("HoldStart");
    int curr = button.GetPressedMS();
    WriteLine(curr);
    curr /= 250;
    WriteLine(curr);
    if(brighntnessWheel)
    {
        SetBrightness(GetBrightness() - curr);
    }
    else
    {
        SetBrightness(GetBrightness() + curr);
    }
    WriteLine(GetBrightness());
    lastCurr = curr;
}

void HoldEnd()
{
    Write("HoldEnd: ");
    WriteLine(button.GetPressedMS());    
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