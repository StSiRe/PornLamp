extern void SaveData();
extern void CloseFS();
bool Debug = true;
//Выводит текст в консоль,если отладка разрешена
void Write(String text)
{
  if(Debug == true)
  {
    Serial.print(text);
  }
}
void Write(int text)
{
  if(Debug == true)
  {
    Serial.print(text);
  }
}
void Write(bool text)
{
  if(Debug == true)
  {
    Serial.print(text);
  }
}
void WriteLine(String text)
{
  if(Debug == true)
  {
    Serial.println(text);
  }
}
void WriteLine(int text)
{
  if(Debug == true)
  {
    Serial.println(text);
  }
}
void WriteLine(bool text)
{
  if(Debug == true)
  {
    Serial.println(text);
  }
}
void WriteLine(size_t text)
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
  SaveData();
  CloseFS();
  Delay(1000);
  ESP.restart();
}