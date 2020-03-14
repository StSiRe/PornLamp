#include <NeoPixelBrightnessBus.h>
extern NeoPixelBrightnessBus<NeoGrbFeature, NeoEsp32I2s1800KbpsMethod> strip;
extern int XY(int x,int y);
extern void Delay(int milliseconds);
extern void ClearMatrix();
extern const int Height;
extern const int Width;
extern int XY(int x,int y);
#define BRIGHT_SPEED 0.015



/*void ToWhite()
{
    for(int k =0;k<16;k++)
    {  
        for(int i=0;i< Width * Height;i++)
        {
            if(strip.GetPixelColor(i).R >= 200 || strip.GetPixelColor(i).G >= 200 || strip.GetPixelColor(i).B >= 200) 
                
                leds[i].fadeLightBy(16);
            else
                leds[i] = CRGB::White;
        }
        FastLED.show();
        Delay(10);
    }
}*/

void LampOn()
{
  for(int i = 0; i < Height; i++)
  {
    for(int j = 0; j < Width; j++)
    {
      strip.SetPixelColor(XY(i,j), RgbColor(255,255,255));
    }
    strip.Show();
    Delay(150);
  }
  Delay(2000);
}
//Анимация при выключении лампы
// void LampOff()
// {
//   //ToWhite();
//   for(int i = Height - 1; i >= 0; i--)
//   {
//     for(int j = 0; j < Width; j++)
//     {
//       leds[XY(i,j)] = CRGB::Black;
//     }
//     FastLED.show();
//     vTaskDelay(150/portTICK_RATE_MS);
//   }
//   FastLED.clear();
//   FastLED.show();
// }
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
          strip.SetPixelColor(XY(j,i), HsbColor(0.6,1,1 - k));
          strip.SetPixelColor(XY(j,anti), HsbColor(0.6,1,1 - k));
        }
        for (size_t j = 0; j < Height; j++)
        {
          strip.SetPixelColor(XY(j,i + 1), HsbColor(0.6,1,k));
          strip.SetPixelColor(XY(j,anti - 1), HsbColor(0.6,1,k));
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
        strip.SetPixelColor(XY(j,i), HsbColor(0.35,1,bright));
        strip.SetPixelColor(XY(j,(Width-1) - i), HsbColor(0.35,1,bright));
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
  for(float col = 0; col < 1; col+= 0.004)
  {
    for(int i = 0; i < 16; i++)
    {
      for(int j = 0; j < 26;j++)
      {
        strip.SetPixelColor(XY(i,(j + (int)(col/0.004))%15), HsbColor(col,1,mask[15 - i][j%15] / 255));
      }
    }
    strip.Show();
    Delay(100);
    ClearMatrix();
  }
  Delay(1000);
}
void StripOff()
{
  for(int i=0;i < Height * Width;i++)
  {
    strip.SetPixelColor(i,RgbColor(0,0,0));
  }
  strip.Show();
}