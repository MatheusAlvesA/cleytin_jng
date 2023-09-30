#include "cleytin_engine.h"
#include "cleytin_audio_engine.h"
#include "cleytin_controls.h"
#include "fase1.h"
#include "fase2.h"

extern "C" {

void app_main(void)
{
    CleytinEngine *engine = new CleytinEngine();
    CleytinControls *controls = new CleytinControls();
    controls->init();
    CleytinAudioEngine *audioEngine = new CleytinAudioEngine();
    audioEngine->init();

    FASE1 *fase1 = new FASE1();
    FASE2 *fase2 = new FASE2();
    while(1) {
        engine->clear(true);
        audioEngine->clear();
        if(fase1->run(engine, controls, audioEngine)) continue;

        engine->clear(true);
        audioEngine->clear();
        if(fase2->run(engine, controls, audioEngine)) continue;
    }
    delete fase1;
    delete fase2;
}

}
