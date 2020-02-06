#include<FastLED.h>


extern CRGB* const leds;
extern const int Height;
extern const int Width;
extern int XY(int x,int y);
extern void Delay(int milliseconds);

//Full circle 240ms
void fadeScreen()
{ 
    for(int k =0;k<16;k++)
    {  
        for(int i=0;i< Width * Height;i++)
        {
            if(leds[i].r >= 40 || leds[i].g >= 40 || leds[i].b >= 40) 
                leds[i].fadeToBlackBy(16);
            else
                leds[i] = 0;
        }
        FastLED.show();
        Delay(1);
    }
    FastLED.clearData();
}
void Sparks() {
    for (byte i = 0; i < 40; i++) {
        byte x = random(0, Width);
        byte y = random(0, Height);
        if (leds[XY(x,y)] == CRGB(0,0,0))
            leds[XY(x, y)] = CHSV(random(0, 255), 255, 255);
        Delay(5);
        FastLED.show();
    }
    fadeScreen();
    FastLED.clearData();
}