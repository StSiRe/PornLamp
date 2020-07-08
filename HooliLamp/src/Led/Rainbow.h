RgbColor Wheel(uint8_t WheelPos) 
{
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) 
  {
    return RgbColor(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) 
  {
    WheelPos -= 85;
    return RgbColor(0, WheelPos * 3, 255 - WheelPos * 3);
  } else 
  {
    WheelPos -= 170;
    return RgbColor(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}


//Для анимаций типа хуя
byte hue = 0;
//Горизонтальная радуга 
void RainbowH()
{    
  hue += 2;
  for (byte j = 0; j < 16; j++) 
  {
    auto color = Wheel(hue + j * 30);
    for (byte i = 0; i < 16; i++)
    {
      strip.SetPixelColor(XY(i, j),color);
    }  
  }
  strip.Show();
  Delay(10);
}
void RainbowV()
{    
  hue += 2;
  for (byte j = 0; j < 16; j++) 
  {
    auto color = Wheel(hue + j * 30);
    for (byte i = 0; i < 16; i++)
    {
      strip.SetPixelColor(XY(j, i),color);
    }  
  }
  strip.Show();
  Delay(10);
}
void Hue()
{
  hue += 2;
  auto color = Wheel(hue);
  for (byte j = 0; j < 16; j++) 
  {
    for (byte i = 0; i < 16; i++)
    {
      strip.SetPixelColor(XY(j, i),color);
    }  
  }
  strip.Show();
  Delay(10);
}