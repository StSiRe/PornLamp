extern void saveSettings();
extern void CloseFS();
extern void LampOff();
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

//Reboot with animation and saving data
void Reset()
{
  LampOff();
  WriteLine("Functions:Starting reboot procedure");
  saveSettings();
  CloseFS();
  //ShowGoodbye animation
  vTaskDelay(1000/15);
  ESP.restart();
}