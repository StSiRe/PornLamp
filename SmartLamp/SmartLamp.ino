
#define stripPin 5
#define stripFrequency 10000
#define stripResolution 8

void setup() 
{
    ledcsetup(0, stripFrequency, stripResolution);
    ledcAttachPin(stripPin,0);
    // ноль в обоих местах канал шим. Отдельную переменную не выделяю так как шим 
    //будет использоватся только один и поидее менять номер этого канала нам не прийдется
}

void loop() {
  ledcWrite(0,255);
}
