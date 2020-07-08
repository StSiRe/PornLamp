//TODO: time of working

void MatrixRoutine()
{
   randomSeed(analogRead(10));
   for(int row = 0; row < Width; row++)
   { 
      if(strip.GetPixelColor(XY(Height - 2, row)).G == 0)
      {
         strip.SetPixelColor(XY(Height - 1, row),RgbColor(0,random(75, 255),0));
      } else if(strip.GetPixelColor(XY(Height - 2, row)).G < 40){
         strip.SetPixelColor(XY(Height - 1, row),RgbColor(0,0,0));
      } else {
         strip.SetPixelColor(XY(Height - 1, row),RgbColor(0,strip.GetPixelColor(XY(Height - 1, row)).G - random(5,30),0));
      }
      strip.Show();
   }
   Delay(5);
   for(int i = 0; i < Height - 1; i++)
   {
      for(int j = 0; j < Width; j++)
      {
         strip.SetPixelColor(XY(i, j),strip.GetPixelColor(XY(i + 1, j)));
      } 
   }
   strip.Show();
   Delay(25);
}