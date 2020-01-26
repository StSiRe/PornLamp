#include<SPIFFS.h>

extern void WriteLine(String text);

//Инициализирует файловое хранилище,и если не получается - пытается починить
void ConfigFS()
{
    WriteLine("Mounting file system...");
    bool tmp = SPIFFS.begin();
    if (tmp)
    {
        WriteLine("FileSystem is mounted without errors");
        return;
    }
    WriteLine("FileSystem is mounted with error");
    WriteLine("System will be try repair FS");
    SPIFFS.format();
    WriteLine("FS formatted");
    WriteLine("Please upload the system files.");    
    //Надо будет сделать автоматическую загрузку с собственного сервера
}