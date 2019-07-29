
#include "Strip.h"

#define stripPinR 15
#define stripPinG 16
#define stripPinB 18
#define stripFrequency 5000
#define stripResolution 8

Strip strip(stripPinR, stripPinG, stripPinB);

void setup() 
{
    strip.Init(stripFrequency,stripResolution);
}

void loop() 
{
  strip.setRGB(0xFF,0xFF,0xFF);
  unsigned long curTime = millis();
  while(millis() - curTime < 1000);
  strip.rainbow();
  curTime = millis();
  while(millis() - curTime < 26000);
}
