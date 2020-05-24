#include <NeoPixelBrightnessBus.h>
extern NeoPixelBrightnessBus<NeoGrbFeature, NeoEsp32I2s1800KbpsMethod> strip;
extern int XY(int x,int y);
extern void Delay(int milliseconds);
extern void ClearMatrix();
extern const int Height;
extern const int Width;
extern int XY(int x,int y);
extern void ClearMatrixTo(RgbColor color);
#define BRIGHT_SPEED 0.015

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
  void LampOn()//включение
  {
    for(int i = 0; i < Height; i++)//цикл бегущий по строкам матрицы снизу вверх
    {
      for(int j = 0; j < Width; j++)//цикл бегущий по столбцам матрицы слева направо
      {
        strip.SetPixelColor(XY(i,j), RgbColor(255,255,255));//изменение цвета пикселя на белый
      }
      strip.Show();//отображение изменений на матрицу
      Delay(150);//задержка для лучшего визуального восприятия
    }
    Delay(2000);//задержка для лучшего визуального восприятия
  }

//Анимация при выключении лампы
void LampOff()
{
  ClearMatrixTo(RgbColor(255,255,255));
  for(int i = Height - 1; i >= 0; i--)
  {
   for(int j = 0; j < Width; j++)
    {
      strip.SetPixelColor(XY(i,j),RgbColor(0,0,0));
    }
    strip.Show();
    Delay(150);
  }
  strip.Show();
}

// //8*256 = 2048 ms = 2 s
void WiFiConnectionProcess() //two blue stripes moves from border to center 8316ms
{
  for (size_t i = 0; i < Width - 1; i++)
  {
      ClearMatrix();
      size_t anti = Width - i - 1;
      if (i == 7)
            continue;
      for(float k=0; k < 1; k += BRIGHT_SPEED)
      {
        for (size_t j = 0; j < Height; j++)
        {
          strip.SetPixelColor(XY(i,j), HsbColor(0.6,1,1 - k));
          strip.SetPixelColor(XY(anti,j), HsbColor(0.6,1,1 - k));
        }
        for (size_t j = 0; j < Height; j++)
        {
          strip.SetPixelColor(XY(i+1,j), HsbColor(0.6,1,k));
          strip.SetPixelColor(XY(anti-1,j), HsbColor(0.6,1,k));
        }
        strip.Show();
        Delay(9);
      }
  }
}

//Подключено к WiFi успешно
void WiFiConnectionSuccess()//green space expending to center 7580ms
{
  for(int i = 0; i < Width/2; i++)
  {
    for(float bright = 0; bright < 1; bright += BRIGHT_SPEED)
    {
      for(int j = 0; j < Height; j++)
      {
        strip.SetPixelColor(XY(i,j), HsbColor(0.35,1,bright));
        strip.SetPixelColor(XY((Width-1) -i, j), HsbColor(0.35,1,bright));
      }
      strip.Show();
      Delay(10);
    }
    Delay(100);
  }
  Delay(1500);
  ClearMatrix();
  strip.Show();
}


byte addByLimit(byte value, byte step, byte limit)
{
    if(value > limit)
    {
        return (value -  step) + (limit/(value -  step)) * (limit%(value -  step));
    }
    return (value +  step) - ((value +  step)/limit) * ((value +  step)%limit);
}

bool sunrise(byte step = 5)
{
  bool isDone = true;
  for(int i = 0; i < 256; i++)
  {
    strip.SetPixelColor(i, RgbColor(
      addByLimit(strip.GetPixelColor(i).R,step,255), 
      addByLimit(strip.GetPixelColor(i).G,step,255), 
      addByLimit(strip.GetPixelColor(i).B,step,170)));
    isDone = (strip.GetPixelColor(i) == RgbColor(252,252,169));
  }
  Delay(1);//Для стабильности
  strip.Show();
  return isDone;
}


float col=0;
void Penis()
{
    int mask[16][16] = {{0, 0, 0, 0, 0, 0, 0, 255, 255, 0, 0, 0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0, 0, 255, 255, 255, 255, 0, 0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0, 0, 255, 255, 255, 255, 0, 0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0, 0, 255, 255, 255, 255, 0, 0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0, 0, 255, 255, 255, 255, 0, 0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0, 0, 255, 255, 255, 255, 0, 0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0, 0, 255, 255, 255, 255, 0, 0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0, 0, 255, 255, 255, 255, 0, 0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0, 0, 255, 255, 255, 255, 0, 0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0, 0, 255, 255, 255, 255, 0, 0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0, 0, 255, 255, 255, 255, 0, 0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0, 0},
                     {0, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0},
                     {0, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0},
                     {0, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0},
                     {0, 0, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 0, 0, 0, 0}};
  
    if(col > 1)
   {    
      col = 0;
   }
    col+= 0.004;
    ClearMatrix();
    for(int i = 0; i < 16; i++)
    {
      for(int j = 0; j < 26;j++)
      {
        strip.SetPixelColor(XY(i,(j + (int)(col/0.004))%15), HsbColor(col,1,mask[15 - i][j%15] / 255));
      }
    }
    strip.Show();
    Delay(100);
}