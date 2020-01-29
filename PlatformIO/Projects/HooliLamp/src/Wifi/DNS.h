#include<ESPmDNS.h>
extern void WriteLine(String text);
//Инициализирует DNS сервер,и подключает к 80 порту
bool ConfigMDNS()
{
    if (!MDNS.begin("lamp")) {
        WriteLine("Error setting up MDNS responder!");
        return false;
    }
    WriteLine("mDNS responder started");
    MDNS.addService("http","tcp",80);
    return true;
}