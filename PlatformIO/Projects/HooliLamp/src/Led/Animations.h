#include<FastLED.h>

extern CRGB leds_plus_safety_pixel[];
extern CRGB* const leds;
extern const int Height;
extern const int Width;
extern int XY(int x,int y);

bool isAnimationEnabled = false;
bool isAnimationGo = false;
bool _updateRequied = false;
String _currentAnimation = "";
xTaskHandle Animation;

#define BRIGHT_SPEED 5

//Анимация при включении лампы
void LampOn()
{
  FastLED.clear();
  FastLED.show();
  for(int i = Height; i >= 0; i--)
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
  for(int i = 0; i >= Height; i++)
  {
    for(int j = 0; j < Width; j++)
    {
      leds[XY(i,j)] = CRGB::White;
    }
    FastLED.show();
    vTaskDelay(150/portTICK_RATE_MS);
  }
  FastLED.clear();
  FastLED.show();
}
//Анимация ожидания подключения к WiFi
/*void WiFiConnectionProcess() //two blue stripes moves from border to center
{
  FastLED.clear();
  for(int i = 1; i < Width - 1; i++)
  {
    for(int j = 0; j < Height; j++)
    {
      leds[XY(j,i - 1)] = CHSV(165,255,50);
      leds[XY(j,i+1)] = CHSV(165,255,125);
      
      leds[XY(j,Width - i)] = CHSV(165,255,50);
      leds[XY(j,Width - i - 2)] = CHSV(165,255,125);
      
      leds[XY(j,Width - i - 1)] = CHSV(165,255,255);
      leds[XY(j,i)] = CHSV(165,255,255);
    }
    FastLED.show();
    vTaskDelay(125/portTICK_RATE_MS);
    if(i == 14) continue;
    for(int j = 0; j < Height; j++)
    {
      leds[XY(j,i - 1)] = CRGB::Black;
      leds[XY(j,Width - i)] = CRGB::Black;
    }
    FastLED.show();
    delay(1);
  }
}
//Подключено к WiFi успешно
void WiFiConnectionSuccess()//green space expending to center
{
  FastLED.clear();
  FastLED.show();
  for(int i = 0; i < Width/2; i++)
  {
    delay(1);
    for(int j = 0; j < Height; j++)
    {
      leds[XY(j,i + 1)] = CHSV(110,255,100);//----- Green shadow
      leds[XY(j,Width - 2 - i)] = CHSV(110,255,100);

      leds[XY(j,i)] = CRGB::Green;//--------------  Main stripe
      leds[XY(j,(Width-1) - i)] = CRGB::Green;
    }
    FastLED.show();
    vTaskDelay(150/portTICK_RATE_MS);
  }
  vTaskDelay(1500/portTICK_RATE_MS);
  FastLED.clear();
  FastLED.show();
}*/

void WiFiConnectionProcess() //two blue stripes moves from border to center
{
  FastLED.clear();
  for(int i = 0; i < Width; i++)
  {
    for(int bright = 0; bright < 0xFF; bright += BRIGHT_SPEED)
    {
      for(int j = 0; j < Height; j++)
      {
        leds[XY(j,i)] = CHSV(165,0xFF,bright);
      }
    }
    FastLED.show();
    vTaskDelay(25/portTICK_RATE_MS);
    for(int bright = 0; bright < 0xFF; bright -= BRIGHT_SPEED)
    {
      for(int j = 0; j < Height; j++)
      {
        leds[XY(j,i)] = CHSV(165,0xFF,bright);
      }
    }
    FastLED.show();
    delay(1);
  }
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

void Rainbow()
{
  for(short correction = 0 ; correction < 256; correction++)
  {
    for (short i = 0; i < Height; i++)
    {
      for(short hue = 0; hue < 0x10; hue++)
      {
        for(short j = 0; j < Width; j--)
        {
          leds[XY(i,j)] = CHSV(15*i + hue + correction ,0xFF,0xFF);
        }
        FastLED.show();
        vTaskDelay(1/portTICK_RATE_MS);
      }
    }
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
        /*
        else if(_currentAnimation == "")
        {

        }
        else if(_currentAnimation == "")
        {

        }
        else if(_currentAnimation == "")
        {

        }
        else if(_currentAnimation == "")
        {

        }*/
        else
        {
            LampOn();
        }
        delay(1);
    }
    vTaskDelete(NULL);
}


void ChangeAnimation(String animationName)
{
    _updateRequied = true;   

    if(Animation!= NULL)
        vTaskDelete(Animation);
    xTaskCreatePinnedToCore(TaskAnimation,"Animation",2048,NULL,1,&Animation,1);
    _currentAnimation=animationName;
}


