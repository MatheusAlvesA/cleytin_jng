#include "cleytin_engine.h"
#include "cleytin_audio_engine.h"
#include "cleytin_controls.h"
#include "fase1.h"

extern "C" {

void app_main(void)
{
    CleytinEngine *engine = new CleytinEngine();
    CleytinControls *controls = new CleytinControls();
    controls->init();
    CleytinAudioEngine *audioEngine = new CleytinAudioEngine();
    audioEngine->init();

    FASE1 *fase1 = new FASE1();
    while(fase1->run(engine, controls, audioEngine));
    delete fase1;
}

}
