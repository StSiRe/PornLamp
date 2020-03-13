#include<SPIFFS.h>
#include<Audio/mp3.h>
extern void Delay(int millisecons);
xTaskHandle AudioControllerTask;


String audioFilePath = "/Sound/Startup.mp3";
bool isAudioPaused = true;
bool isEnabled = false;

void Controller(void *parameter)
{
    for(;;)
    {
        mp3_play();
        Delay(15);
    }
}
void PlayAudio(String path)
{
    audioFilePath = path;
    mp3_setup(audioFilePath);
    if(AudioControllerTask != NULL)
        vTaskDelete(AudioControllerTask);
    isAudioPaused == false;
    isEnabled = true;
    xTaskCreatePinnedToCore(Controller,"Audio Controller Task",8192,NULL,3,&AudioControllerTask,1);
}
void PlayAudio()
{
    PlayAudio(audioFilePath);    
}

void PauseAudio()
{
    //isAudioPaused == true;
    //isEnabled = false;
}
//void StopAudio()
//{
//    isAudioPaused == true;
//    mp3_stop();
//}
