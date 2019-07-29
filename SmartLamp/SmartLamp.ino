
#include "Strip.h"

#define stripPinR 15
#define stripPinG 16
#define stripPinB 18
#define stripFrequency 5000
#define stripResolution 8

enum channels 
{
  RED, GREEN, BLUE
};

void setup() 
{
    ledcAttachPin(stripPinR,RED);
    ledcAttachPin(stripPinG,GREEN);
    ledcAttachPin(stripPinB,BLUE);
    ledcSetup(RED, stripFrequency, stripResolution);
    ledcSetup(GREEN, stripFrequency, stripResolution);
    ledcSetup(BLUE, stripFrequency, stripResolution);
}

void loop() {
  ledcWrite(RED,255);
  ledcWrite(GREEN,255);
  ledcWrite(BLUE,255);
}
