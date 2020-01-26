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