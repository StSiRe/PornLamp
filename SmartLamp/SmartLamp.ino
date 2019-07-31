
#include "Strip.h"

#define stripPinR 5
#define stripPinG 19
#define stripPinB 18
#define stripFrequency 20000
#define stripResolution 8

Strip strip(stripPinR, stripPinG, stripPinB);

void setup() 
{
    strip.Init(stripFrequency,stripResolution);
}

void loop() 
{
  
  strip.sunrise();
  //strip.rainbow();
}
