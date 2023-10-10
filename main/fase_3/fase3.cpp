#include "fase3.h"

FASE3::FASE3() {
    this->mainShipDestroyed = false;
    this->timerToPass = NULL;
}

bool FASE3::run(CleytinEngine *engine, CleytinControls *controls, CleytinAudioEngine *audioEngine, bool pacifist) {
    this->engine = engine;
    this->audioEngine = audioEngine;
    this->controls = controls;
    this->pacifist = pacifist;

    this->opening();

    CleytinAudio *audio = NULL;
    this->audioEngine->createAudio(wav_bin_musica_fundo, &audio);
    audio->setLoop(true);
    audio->play();

    this->setupBackground();
    this->setupMainShip();

    uint64_t start = esp_timer_get_time();
    uint64_t sum = 0;
    uint64_t n = 0;
    uint64_t loopTime = 0;
    uint64_t renderTime = 0;
    while(
        !this->mainShipDestroyed &&
        !this->pacificPass()
    ) {
        uint64_t startLoop = esp_timer_get_time();
        loopTime += engine->loop();
        renderTime += engine->render();
        n++;
        sum = sum + (esp_timer_get_time() - startLoop);
        if((esp_timer_get_time() - start) > 500 * 1000) {
            printf(
                "FPS: %llu | Objects: %u | loop time: %llu | render time: %llu\n",
                n * 2,
                engine->getObjectsCount(),
                (loopTime / 1000) / n,
                (renderTime / 1000) / n
            );
            start = esp_timer_get_time();
            sum = 0;
            n = 0;
            loopTime = 0;
            renderTime = 0;
        }
    }

    if(this->mainShipDestroyed) {
        this->clean();
        this->gameOver();
        return true;
    }

    this->clean();
    return false;
}

bool FASE3::pacificPass() {
    if(this->timerToPass == NULL) return false;
    return this->timerToPass->check();
}

void FASE3::clean() {
    this->engine->clear(true);
    this->audioEngine->clear();
    this->mainShipDestroyed = false;
    if(this->timerToPass != NULL) {
        delete this->timerToPass;
        this->timerToPass = NULL;
    }
}

void FASE3::onEnemyDestroyed() {
    //TODO
}

void FASE3::onMainShipDestroyed() {
    this->mainShipDestroyed = true;
}

void FASE3::opening() {
    CERectangle *rect = new CERectangle();
    rect->setBaseColor({0, 0, 0});
    rect->setHeight(240);
    rect->setWidth(320);
    rect->setPos(0, 0);
    rect->setFilled(true);
    this->engine->addObject(rect);

    CEText *text = new CEText();
    text->setText("ÚLTIMA FASE");
    text->setBaseColor({255, 255, 255});
    text->setSizeMultiplier(3);
    text->setPos(25, 90);
    text->setPriority(2);
    this->engine->addObject(text);

    this->engine->loopAndRender();
    cleytin_delay(3000);

    this->engine->clear(true);
}

void FASE3::gameOver() {
    this->setupBackground();

    CEText *text = new CEText();
    text->setText("GAME OVER");
    text->setBaseColor({255, 0, 0});
    text->setSizeMultiplier(3);
    text->setPos(50, 100);
    this->engine->addObject(text);

    while(!this->controls->getStart()) {
        this->engine->loopAndRender();
    }

    this->engine->clear(true);
}


void FASE3::setupBackground() {
    CEColorfulBitmap *bitmap = new CEColorfulBitmap();
    bitmap->setBuffer(this->pacifist ? sprite_color_bg_02 : sprite_color_bg_03);
    bitmap->setHeight(240);
    bitmap->setWidth(320);
    bitmap->setColisionEnabled(false);
    bitmap->setHasTransparency(false);
    this->engine->addObject(bitmap);
}

void FASE3::setupMainShip() {
    MainShip *mainShip = new MainShip();
    mainShip->setControls(this->controls);
    mainShip->setAudioInterface(this->audioEngine);
    mainShip->setOnMainShipDestroyed([&](){
        this->onMainShipDestroyed();
    });
    this->engine->addObject(mainShip);
}
