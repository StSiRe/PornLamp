#ifndef SYSTEM_FUNCTIONS
#define SYSTEM_FUNCTIONS
extern void SaveData();
extern void CloseFS();
bool Debug = false;

//Выводит текст в консоль,если отладка разрешена
template <class T>
void Write(T data)
{
  if(Debug)
  {
    Serial.print(data);
  }
}

template <class T>
void WriteLine(T text)
{
  if(Debug)
  {
    Serial.println(text);
  }
}
//преобразование string -> char
char* ToChar(String command)
{
    if(command.length()!=0){
        char *p = const_cast<char*>(command.c_str());
        return p;
    }
    return nullptr;
}

//Ожидание некоторое время
//Used vTaskDelay()
void Delay(int milliseconds)
{
  vTaskDelay(milliseconds/portTICK_PERIOD_MS);
}

//Перезагрузак с сохранением данных
void Reset()
{
  Log.addLog("Starting reboot procedure","Functions.h");
  SaveData();
  CloseFS();
  Delay(1000);
  ESP.restart();
}
#endif