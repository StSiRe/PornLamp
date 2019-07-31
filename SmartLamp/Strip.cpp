#include "Strip.h"

enum ledChannels 
{
  RED, GREEN, BLUE
};

Strip::Strip(byte stripPinR, byte stripPinG, byte stripPinB)
{
    ledcAttachPin(stripPinR,RED);
    ledcAttachPin(stripPinG,GREEN);
    ledcAttachPin(stripPinB,BLUE);
    _red = _green = _blue = 0;
    readyToWork = false; 
}

void Strip::Init(int stripFrequency, byte stripResolution)
{
    ledcSetup(RED, stripFrequency, stripResolution);
    ledcSetup(GREEN, stripFrequency, stripResolution);
    ledcSetup(BLUE, stripFrequency, stripResolution);
    readyToWork = true;
    autoSend = true;
}

void Strip::setRGB(byte red, byte green, byte blue)
{
  _red = red;
  _green = green;
  _blue = blue; 
  if(autoSend) 
  {
    sendToStrip();
  }
}

void Strip::setHUE(byte hue, byte brightness)
{
  hueToRGB(hue, brightness);
  if(autoSend) 
  {
    sendToStrip();
  }
}

void Strip::sendToStrip()
{
  if(!readyToWork) return;
  ledcWrite(RED,_red);//---->
  ledcWrite(GREEN,_green);//--->     ledcWrite(ledChannel, dutyCycle);
  ledcWrite(BLUE,_blue);//-->
}

void Strip::hueToRGB(uint8_t hue, uint8_t brightness)
{
    uint16_t scaledHue = (hue * 6);
    uint8_t segment = scaledHue / 256; // segment 0 to 5 around the
                                            // color wheel
    uint16_t segmentOffset =
      scaledHue - (segment * 256); // position within the segment

    uint8_t complement = 0;
    uint16_t prev = (brightness * ( 255 -  segmentOffset)) / 256;
    uint16_t next = (brightness *  segmentOffset) / 256;

    if(true)
    {
      brightness = 255 - brightness;
      complement = 255;
      prev = 255 - prev;
      next = 255 - next;
    }

    switch(segment ) {
    case 0:      // red
        _red = brightness;
        _green = next;
        _blue = complement;
    break;
    case 1:     // yellow
        _red = prev;
        _green = brightness;
        _blue = complement;
    break;
    case 2:     // green
        _red = complement;
        _green = brightness;
        _blue = next;
    break;
    case 3:    // cyan
        _red = complement;
        _green = prev;
        _blue = brightness;
    break;
    case 4:    // blue
        _red = next;
        _green = complement;
        _blue = brightness;
    break;
   case 5:      // magenta
    default:
        _red = brightness;
        _green = complement;
        _blue = prev;
    break;
    }
}

void Strip::rainbow(int delayTime)
{
  for (byte color = 0; color < 255; color++) 
  {    
    setHUE(color, 255); 
    vTaskDelay(delayTime);
  };
}

void Strip::sunrise()
{
  
  for(int brt = 0; brt <= 255; brt++)
  {
     setRGB(brt,min(brt,200),0);
     delay(50);
  }
  for(byte brt = 0; brt <= 255; brt++)
  {
     setRGB(0xFF,min(200 + brt, 255),brt);
     //strip.setRGB(0xFF,0xC8,0x00);
     delay(100);
  }
  delay(10000);
}















