#include<FastLED.h>
#include<Led/Fire.h>
#include<Led/SystemAnimations.h>
#include<string.h>


extern CRGB leds_plus_safety_pixel[];
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
};

void fadeScreen()
{ 
    for(int k =0;k<16;k++)
    {  
        for(int i=0;i< Width * Height;i++)
        {
                if(leds[i].r >= 40 || leds[i].g >= 40 || leds[i].b >= 40) 
                {
                    leds[i].fadeToBlackBy(16);
                }
                else
                {
                    leds[i] = 0;
                }   
        }
        FastLED.show();
        vTaskDelay(1/portTICK_RATE_MS);
    }
    FastLED.clearData();
}
void Sparks() {
  for (byte i = 0; i < 40; i++) {
    byte x = random(0, Width);
    byte y = random(0, Height);
    if (leds[XY(x,y)] == CRGB(0,0,0))
      leds[getPixelNumber(x, y)] = CHSV(random(0, 255), 255, 255);
      delay(5);
    FastLED.show();
  }
  fadeScreen();
  FastLED.clearData();
}

//Для анимаций типа хуя
byte hue = 0;
//Горизонтальная радуга 
void RainbowH()
{    
  hue += 2;
  for (byte j = 0; j < Height; j++) 
  {
    CHSV thisColor = CHSV((byte)(hue + j * 30), 255, 255);
    for (byte i = 0; i < Width; i++)
      leds[XY(i,j)] = thisColor;
  }
  FastLED.show();
  delay(10);
  FastLED.clearData();
}
//Вертикальная радуга
void RainbowV()
{    
  hue += 2;
  for (byte j = 0; j < Height; j++) 
  {
    CHSV thisColor = CHSV((byte)(hue + j * 30), 255, 255);
    for (byte i = 0; i < Width; i++)
      leds[XY(j,i)] = thisColor;
  }
  FastLED.show();
  delay(10);
  FastLED.clearData();
}
//хуя анимация для всей матрицы
void HueAnimation()
{
    for(int hue; hue< 256; hue++)
    {
        for(int i=0; i< Height * Width; i++)
        {
                leds[i] = CHSV(hue,255,255);
        }
        FastLED.show();
        delay(25);
    }
}

void TaskAnimation(void *pvParameter)
{
    for (;;)
    {
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
            fireRoutine();
            vTaskDelay(5/portTICK_RATE_MS);
            FastLED.show();
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
        /*
        else if(_currentAnimation == "")
        {

        }*/
        else
        {
            LampOn();
        }
        vTaskDelay(1/portTICK_RATE_MS);
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
void ChangeAnimation(String animationName)
{
    //WriteLine("Changing Animation" + animationName);
    
    if(Animation!= NULL)
        vTaskDelete(Animation);
    //delay(500);
    xTaskCreatePinnedToCore(TaskAnimation,"Animation",2048,NULL,1,&Animation,1);
    _currentAnimation=animationName;
    //currentAnimationNum = strAnim2Num(animationName);
}


