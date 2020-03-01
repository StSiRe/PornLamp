extern void saveSettings();
extern void CloseFS();
bool Debug = true;
//Выводит текст в консоль,если отладка разрешена
void WriteLine(String text)
{
  if(Debug == true)
  {
    Serial.println(text);
  }
}

char* ToChar(String command){
    if(command.length()!=0){
        char *p = const_cast<char*>(command.c_str());
        return p;
    }
    return NULL;
}

//Ожидание в некоторое время
//Used vTaskDelay()
void Delay(int milliseconds)
{
  vTaskDelay(milliseconds/portTICK_PERIOD_MS);
}

//Reboot with animation and saving data
void Reset()
{
  WriteLine("Functions:Starting reboot procedure");
  saveSettings();
  CloseFS();
  Delay(1000);
  ESP.restart();
}


bool isUpdEnabled = true;