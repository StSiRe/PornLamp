#include <NeoPixelBrightnessBus.h>
extern NeoPixelBrightnessBus<NeoGrbFeature, NeoEsp32I2s1800KbpsMethod> strip;
extern int XY(int x,int y);
extern void Delay(int milliseconds);
extern const int Height;
extern const int Width;

//TODO: time of working

void MatrixRoutine()
{
   //strip.SetPixelColor(XY(1, 1), RgbColor(255,255,255));
   //strip.Show();
   //delay(50000);
   randomSeed(analogRead(10));
   for(int row = 0; row < Width; row++)
   { 
      if(strip.GetPixelColor(XY(Height - 2, row)).G == 0)
      {
         strip.SetPixelColor(XY(Height - 1, row),RgbColor(0,random(75, 255),0));
      } else if(strip.GetPixelColor(XY(Height - 2, row)).G < 40){
         strip.SetPixelColor(XY(Height - 1, row),RgbColor(0,0,0));
      } else {
         strip.SetPixelColor(XY(Height - 1, row),RgbColor(0,strip.GetPixelColor(XY(Height - 1, row)).G - random(5,30),0));
      }
      strip.Show();
   }
   Delay(5);
   for(int i = 0; i < Height - 1; i++)
   {
      for(int j = 0; j < Width; j++)
      {
         strip.SetPixelColor(XY(i, j),strip.GetPixelColor(XY(i + 1, j)));
      } 
   }
   strip.Show();
   Delay(25);
}