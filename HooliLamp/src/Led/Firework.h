void Firework()
{    
    for (byte i = 0; i < 40; i++) {
        byte x = random(0, Width);
        byte y = random(0, Height);
        if (strip.GetPixelColor(XY(x,y)) == RgbColor(0,0,0))
            strip.SetPixelColor(XY(x, y),HsbColor((float)(random(0, 256)) / (float)256, 1, 1));        
    }
    Delay(15);
    strip.Show();
    fadeScreen();
}