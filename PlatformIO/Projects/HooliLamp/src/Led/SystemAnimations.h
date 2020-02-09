#include<FastLED.h>

extern CRGB leds_plus_safety_pixel[];
extern CRGB* const leds;
extern const int Height;
extern const int Width;
extern int XY(int x,int y);
#define BRIGHT_SPEED 4


void ToWhite()
{
    for(int k =0;k<16;k++)
    {  
        for(int i=0;i< Width * Height;i++)
        {
            if(leds[i].r >= 200 || leds[i].g >= 200 || leds[i].b >= 200) 
                leds[i].fadeLightBy(16);
            else
                leds[i] = CRGB::White;
        }
        FastLED.show();
        Delay(10);
    }
}

void LampOn()
{
  FastLED.clear();
  FastLED.show();
  for(int i = 0; i < Height; i++)
  {
    for(int j = 0; j < Width; j++)
    {
      leds[XY(i,j)] = CRGB::White;
    }
    FastLED.show();
    vTaskDelay(150/portTICK_RATE_MS);
  }
  vTaskDelay(2000/portTICK_RATE_MS);
  FastLED.clear();
  FastLED.show();
}
//Анимация при выключении лампы
void LampOff()
{
  FastLED.clear();
  FastLED.show();
  ToWhite();
  for(int i = Height - 1; i >= 0; i--)
  {
    for(int j = 0; j < Width; j++)
    {
      leds[XY(i,j)] = CRGB::Black;
    }
    FastLED.show();
    vTaskDelay(150/portTICK_RATE_MS);
  }
  FastLED.clear();
  FastLED.show();
}
//8*256 = 2048 ms = 2 s
void WiFiConnectionProcess() //two blue stripes moves from border to center
{
  FastLED.clear();
  FastLED.show();
  for (size_t i = 0; i < Width/2 - 1; i++)
  {
      FastLED.clear();
      size_t anti = Width - i - 1;
      for(int k=0; k < 256; k += BRIGHT_SPEED)
      {
        for (size_t j = 0; j < Height; j++)
        {
            leds[XY(j,i)] = CHSV(170,255,255 -k);
            leds[XY(j,anti)] = CHSV(170,255,255 -k);
        }
        for (size_t j = 0; j < Height; j++)
        {
            leds[XY(j,i + 1)] = CHSV(170,255,k);
            leds[XY(j,anti - 1)] = CHSV(170,255,k);
        }
        FastLED.show();
        vTaskDelay(5/portTICK_RATE_MS);
      }
  }
  FastLED.clear();
  FastLED.show();
  FastLED.clearData();
}

//Подключено к WiFi успешно
void WiFiConnectionSuccess()//green space expending to center
{
  FastLED.clear();
  FastLED.show();
  for(int i = 0; i < Width/2; i++)
  {
    delay(1);
    for(int bright = 0; bright < 0xFF; bright += BRIGHT_SPEED)
    {
      for(int j = 0; j < Height; j++)
      {
        leds[XY(j,i)] = CHSV(90,0xFF,bright);
        leds[XY(j,(Width-1) - i)] = CHSV(90,0xFF,bright);
      }
      FastLED.show();
      vTaskDelay(1/portTICK_RATE_MS);
    }
    vTaskDelay(150/portTICK_RATE_MS);
  }
  vTaskDelay(1500/portTICK_RATE_MS);
  FastLED.clear();
  FastLED.show();
}