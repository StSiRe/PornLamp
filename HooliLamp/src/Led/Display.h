#include <NeoPixelBrightnessBus.h>
const uint16_t PixelCount = 256;
const uint16_t PixelPin = 12;
NeoPixelBrightnessBus<NeoGrbFeature, NeoEsp32I2s1800KbpsMethod> strip(PixelCount, PixelPin);

const int Height = 16;
const int Width = 16;

const bool  MatrixSerpentineLayout = true;
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
  strip.Begin();
  strip.SetBrightness(64);
  strip.Show();
  
}
void ChangeBrightness(int brightness)
{
    //strip.SetBrightness(brightness);
}
