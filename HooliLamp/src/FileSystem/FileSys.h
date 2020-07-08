#include<SPIFFS.h>

//Инициализирует файловое хранилище,и если не получается - пытается починить
void ConfigFS()
{
    WriteLine("Mounting file system...");
    bool tmp = SPIFFS.begin();
    if (tmp)
    {
        Log.addLog("FileSystem is mounted succesfuly", "FileSys.h", 1);
        float percentage  = (float)SPIFFS.usedBytes()/(float)SPIFFS.totalBytes()*100;
        WriteLine(String(percentage)+ " Free space");
        return;
    }
    Log.addLog("FileSystem is mounted with error", "FileSys.h",-1);
    WriteLine("System will be try repair FS");
    SPIFFS.format();
    WriteLine("FS formatted");
    WriteLine("Please upload the system files.");    
    //Надо будет сделать автоматическую загрузку с собственного сервера
}

void CloseFS()
{
    WriteLine("Closing FS");
    SPIFFS.end();
    Log.addLog("FS is closed", "FileSys.h");
}