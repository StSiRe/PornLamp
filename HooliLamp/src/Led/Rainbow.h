#include<FastLED.h>


extern CRGB* const leds;
extern const int Height;
extern const int Width;
extern int XY(int x,int y);
extern void Delay(int milliseconds);



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
  Delay(10);
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
  Delay(10);
  FastLED.clearData();
}


byte huec = 0;
//хуя анимация для всей матрицы
void HueAnimation()
{
    for(int i=0; i< Height * Width; i++)
    {
        leds[i] = CHSV(huec,255,255);
    }
    FastLED.show();
    Delay(25);
    huec++;
}