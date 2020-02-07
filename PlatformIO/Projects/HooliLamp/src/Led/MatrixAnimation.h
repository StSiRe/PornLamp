#include<FastLED.h>


extern CRGB* const leds;
extern const int Height;
extern const int Width;
extern int XY(int x,int y);
extern void Delay(int milliseconds);

//TODO: time of working

void matrixRoutine()
{
   for(int row = 0; row < Width; row++)
   { 
      if(leds[XY(Height - 2, row)].g == 0)
      {
         leds[XY(Height - 1, row)].g = random(0, 255);
      } else if(leds[XY(Height - 2, row)].g < 35){
         leds[XY(Height - 1, row)].g = 0;
      } else {
         leds[XY(Height - 1, row)].g -= 20;
      }
      FastLED.show();
   }
   Delay(10);
   for(int i = 0; i < Height - 1; i++)
   {
      for(int j = 0; j < Width; j++)
      {
         leds[XY(i, j)] = leds[XY(i + 1, j)];
      } 
   }
   FastLED.show();
}