#include<NeoPixelBrightnessBus.h>

extern NeoPixelBrightnessBus<NeoGrbFeature, NeoEsp32I2s1800KbpsMethod> strip;

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
            int r = strip.GetPixelColor(i).R;
            int g = strip.GetPixelColor(i).G;
            int b = strip.GetPixelColor(i).B;
            if(r >= 40 || g >= 40 || b >= 40) 
            {
                if(r>16)
                r -= 16;
                if(b>16)
                b -= 16;
                if(g>16)
                g -= 16;

                strip.SetPixelColor(i,RgbColor(r,g,b));
            }
            else
                strip.SetPixelColor(i,RgbColor(0,0,0));
        }
        strip.Show();
        Delay(1);
    }
}
void Sparks() {
    for (byte i = 0; i < 40; i++) {
        byte x = random(0, Width);
        byte y = random(0, Height);
        if (strip.GetPixelColor(XY(x,y)) == RgbColor(0,0,0))
            strip.SetPixelColor(XY(x, y),HsbColor((float)(random(0, 256)) / (float)256, 1, 1));
        Delay(15);
        strip.Show();
    }
    fadeScreen();
}