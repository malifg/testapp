#include "audiotest.h"

AudioTest::AudioTest()
{
}

int AudioTest::initialize(){
    testStart = false;
}

void AudioTest::run(){
    while(true){
        if(testStart){
            playSound();
            testStart = false;
        }
    }
}

int AudioTest::playSound(){
    _processAplay.execute("aplay", QStringList("/usr/share/sounds/alsa/Front_Center.wav"));
}
