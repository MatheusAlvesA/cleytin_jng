#include "cleytin_engine.h"
#include "cleytin_audio_engine.h"
#include "cleytin_controls.h"
#include "fase1.h"
#include "fase2.h"
#include "fase3.h"
#include "tela_final.h"

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
    FASE3 *fase3 = new FASE3();
    TelaFinal *telaFinal = new TelaFinal();
    while(1) {
        engine->clear(true);
        audioEngine->clear();
        if(fase1->run(engine, controls, audioEngine)) continue;

        engine->clear(true);
        audioEngine->clear();
        bool pacifist = true;
        if(fase2->run(engine, controls, audioEngine, &pacifist)) continue;

        engine->clear(true);
        audioEngine->clear();
        if(fase3->run(engine, controls, audioEngine, &pacifist)) continue;

        engine->clear(true);
        audioEngine->clear();
        if(telaFinal->run(engine, audioEngine, pacifist)) continue;
    }
    delete fase1;
    delete fase2;
    delete fase3;
    delete telaFinal;
    delete engine;
    delete controls;
    delete audioEngine;
}

}
