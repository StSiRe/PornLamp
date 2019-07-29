
#define stripPinR 15
#define stripPinG 16
#define stripPinB 18
#define stripFrequency 5000
#define stripResolution 8

void setup() 
{
    ledcsetup(0, stripFrequency, stripResolution);
    ledcAttachPin(stripPinR,0);
    ledcAttachPin(stripPinG,1);
    ledcAttachPin(stripPinB,2);
    // ноль в обоих местах канал шим. Отдельную переменную не выделяю так как шим 
    //будет использоватся только один и поидее менять номер этого канала нам не прийдется
}

void loop() {
  ledcWrite(0,255);
  ledcWrite(1,255);
  ledcWrite(2,255);
}
