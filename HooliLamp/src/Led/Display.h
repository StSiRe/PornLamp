#include <FastLED.h>
#define BRIGHTNESS 64
#define COLOR_ORDER GRB
#define CHIPSET WS2812B
#define LED_PIN 12

const int Height = 16;
const int Width = 16;
#define NUM_LEDS (Width * Height)
const bool  MatrixSerpentineLayout = true;
CRGB leds_plus_safety_pixel[ NUM_LEDS + 1];
CRGB* const leds(leds_plus_safety_pixel + 1);

int XY( int x, int y)
{
  int i;  
  if( MatrixSerpentineLayout == false) {
    i = (y * Width) + x;
  }
  if( MatrixSerpentineLayout == true) {
    if( y & 0x01) {
      // Odd rows run backwards
      int reverseX = (Width - 1) - x;
      i = (y * Width) + reverseX;
    } else {
      // Even rows run forwards
      i = (y * Width) + x;
    }
  }
  return i;
}

void InitMatrix()
{
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalSMD5050);
  FastLED.setBrightness(BRIGHTNESS);
}

//Устанавливает максимальную яркость на диодах
void SetBrightness(int brightness)
{
  FastLED.setBrightness(brightness);
  FastLED.show();
}

//Очищает экран и полностью чистит буфер
void ClearFastLED()
{
  FastLED.clear();
  FastLED.clearData();
  FastLED.show();
}





