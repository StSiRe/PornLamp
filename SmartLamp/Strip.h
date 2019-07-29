#ifndef Strip_h
#define Strip_h

#include "Arduino.h"

class Strip
{
  public:
    //***********ИНИЦИАЛИЗАЦИЯ***********
    Strip(byte stripPinR, byte stripPinG, byte stripPinB); // 
    void Init(int stripFrequency, byte stripResolution); // инициализация основных настроек ленты
    
    //*********СЛУЖЕБНЫЕ_ФУНКЦИИ*********
    void setHUE(byte hue, byte brightness);
    void setRGB(byte red, byte green, byte blue);
    void sendToStrip(); // функция обновления ленты

    //*************ЭФФЕКТЫ***************
    void rainbow(int delayTime = 100);
  private:
    void hueToRGB(uint8_t hue, uint8_t brightness); // функция преобразования цветовых стандартов
    bool readyToWork; // флаг готовности ленты для работы
    bool autoSend; //после смены цвета автоматически выводить его на ленту (по умолчанию true)
    byte _red, _green, _blue;
    
};

#endif
