#include <Arduino.h>
#include <FastLED.h>

#define BRIGHTNESS 64
#define COLOR_ORDER GRB
#define CHIPSET WS2811
#define LED_PIN 12

const uint8_t Height = 16;
const uint8_t Width = 16;
#define NUM_LEDS (Width * Height)
const bool  MatrixSerpentineLayout = true;
CRGB leds_plus_safety_pixel[ NUM_LEDS + 1];
CRGB* const leds( leds_plus_safety_pixel + 1);

//--------------------SPIZJENO---------------------
uint16_t XY( uint8_t x, uint8_t y)
{
  uint16_t i;
  
  if( MatrixSerpentineLayout == false) {
    i = (y * Width) + x;
  }

  if( MatrixSerpentineLayout == true) {
    if( y & 0x01) {
      // Odd rows run backwards
      uint8_t reverseX = (Width - 1) - x;
      i = (y * Width) + reverseX;
    } else {
      // Even rows run forwards
      i = (y * Width) + x;
    }
  }
  return i;
}
//------------------------------------------

void initMatrix()
{
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalSMD5050);
  FastLED.setBrightness(BRIGHTNESS);
}

void WiFiConnectionProcess() //two blue stripes moves from border to center
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
    delay(125);
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

void WiFiConnectionSucces()//green space expending to center
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
    delay(150);
  }
  delay(2000);
  FastLED.clear();
  FastLED.show();
}

void Start()
{
  FastLED.clear();
  FastLED.show();
  for(int i = Height - 1; i >= 0; i--)
  {
    for(int j = 0; j < Width; j++)
    {
      leds[XY(i,j)] = CRGB::White;
    }
    FastLED.show();
    delay(150);
  }
  delay(1500); 
  FastLED.clear();
  FastLED.show();
}



void setup() {
  initMatrix();
}

void loop() {
  Start();
  delay(1000);
  WiFiConnectionProcess();
  WiFiConnectionProcess();
  WiFiConnectionProcess();
  WiFiConnectionSucces();
  delay(2000);
}
