#include <NeoPixelBrightnessBus.h>
//Общее количество пикселей
const uint16_t PixelCount = 256;
//Пин подключения матрицы к мк
const uint16_t PixelPin = 27;
//Яркость для всей ленты
int _brightness = 64;
//Максимальная допустима яркость ленты
//Использовать для ограничения потребления тока
int _maxBrightness = 255;

NeoPixelBrightnessBus<NeoGrbFeature, NeoEsp32I2s1800KbpsMethod> strip(PixelCount, PixelPin);

//Кол-во пикселей в высоту
const int Height = 16;
//Кол-во пикселей в длину
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

//Инициализация матрицы
void InitMatrix()
{
  strip.Begin();
  strip.SetBrightness(_brightness);
  strip.Show();  
}
int CheckNewBrightness(int brightness)
{  
  if(brightness > 255)
    brightness = 255;
  if(brightness < 0)
    brightness =0;
    return brightness;
}
void SetMaxBrightness(int newBrightness)
{
  _maxBrightness = CheckNewBrightness(newBrightness);
  if(_brightness > _maxBrightness) SetBrightness(_maxBrightness);
}
int GetMaxBrightness()
{
  return _maxBrightness;
}
//Установить абсолютную яркость для всей матрицы
void SetBrightness(int brightness)
{
  brightness = CheckNewBrightness(brightness);
  if(brightness != _brightness)
  {    
    _brightness = brightness;
    strip.SetBrightness(_brightness);
  }
}

//Очищает экран заливая его указанным цветом
void CrearMatrixTo(RgbColor color)
{
  for(int i = 0; i < Height * Width; ++i)
  {
    strip.SetPixelColor(i, color);
  }
  strip.Show();
}

//Очистить экран(на черный цвет)
void ClearMatrix()
{
  CrearMatrixTo(RgbColor(0,0,0));
}
//Значение яркости до момента выключения матрицы,не использовать нигде
int _lastBrightness = 0;
//Выключает матрицу(Яркость - 0)
void OffMatrix()
{
  _lastBrightness = _brightness;
  SetBrightness(_brightness);
}
//Включает матрицу(ставит предыдущее значение яркости)
void OnMatrix()
{
  SetBrightness(_lastBrightness);
}
int GetBrightness()
{
  return (int)_brightness;
}