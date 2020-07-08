#define PowerPin 27
#define PowerMatrixRelayPin 22

//---------------Battery------------------------
bool  _batteryMode = false;
bool PowerMode = true;
void _TaskBatteryWachter(void *param);

void InitBattery(bool isEnabled)
{
    if(isEnabled)
    {
        xTaskCreatePinnedToCore(_TaskBatteryWachter,"Battery watcher",2048,NULL,1,NULL,0);
        WriteLine("Battery Watcher started...");
        pinMode(PowerPin,INPUT);
        pinMode(PowerMatrixRelayPin,OUTPUT);
        digitalWrite(PowerMatrixRelayPin,HIGH);
    }
}
void _TaskBatteryWachter(void *param)
{
    for (;;)
    {
        Delay(100);
        int data = digitalRead(PowerPin);
        //Serial.println(data);
        if(data == 0)
        {
            if(!_batteryMode)
            {
                Log.addLog("No input power supply. System is going to battery supply power mode.", "Battery.h");
            }
            _batteryMode = true;
            SetMaxBrightness(GetMaxBrightness()/100 * 50);//50% от обычной максималки
            if(PowerMode == true)
            {
                digitalWrite(PowerMatrixRelayPin,LOW);
                
            }
        }
        if(data == 1)
        {
            if(_batteryMode)
            {
                Log.addLog("Have input power supply", "Battery.h");
            }
            _batteryMode = false;
            //Serial.println("Have input power supply");
            SetMaxBrightness(GetMaxBrightness()/100 * 200);//100% от обычной максималки
            if(PowerMode == true)
            {
                digitalWrite(PowerMatrixRelayPin,HIGH);
            }
        }
    }
    vTaskDelete(NULL);
}
//-------------------------Matrix -------------------
//Значение яркости до момента выключения матрицы,не использовать нигде
int _lastBrightness = 255;

//Выключает матрицу(Яркость - 0)
void OffMatrix()
{
    Log.addLog("Turning matrix off", "Battery.h");
    _lastBrightness = _brightness;
    SetBrightness(0);
    PowerMode = false;
}
//Включает матрицу(ставит предыдущее значение яркости)
void OnMatrix()
{
    Log.addLog("Turning matrix on", "Battery.h");
    SetBrightness(_lastBrightness);
    PowerMode = true;
}