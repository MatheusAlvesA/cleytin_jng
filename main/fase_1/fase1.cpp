#include "fase1.h"

FASE1::FASE1() {
    this->scoreText = NULL;
    this->lastMeteorSpawn = 0;
    this->score = 0;
    this->mainShipDestroyed = false;
}

bool FASE1::run(CleytinEngine *engine, CleytinControls *controls, CleytinAudioEngine *audioEngine) {
    this->engine = engine;
    this->audioEngine = audioEngine;
    this->controls = controls;

    this->opening();

    CleytinAudio *audio = NULL;
    this->audioEngine->createAudio(wav_bin_musica_fundo, &audio);
    audio->setLoop(true);
    audio->play();

    this->setupBackground(true);
    this->setupMainShip();

    uint64_t start = esp_timer_get_time();
    uint64_t sum = 0;
    uint64_t n = 0;
    uint64_t loopTime = 0;
    uint64_t renderTime = 0;
    this->updateScoreDisplay();
    while(!this->mainShipDestroyed && this->score < SCORE_TO_PASS) {
        uint64_t startLoop = esp_timer_get_time();
        this->spawnMeteor();
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

void FASE1::clean() {
    this->engine->clear(true);
    this->audioEngine->clear();
    this->scoreText = NULL;
    this->mainShipDestroyed = false;
    this->score = 0;
    this->lastMeteorSpawn = 0;
}

void FASE1::spawnMeteor() {
    uint64_t elapsed_time_ms = (esp_timer_get_time() - this->lastMeteorSpawn) / 1000;

    if(elapsed_time_ms < METEOR_SPAWN_INTERVAL) {
        return;
    }

    DefaultMeteor *meteor = new DefaultMeteor();
    meteor->setPos(rand() % 245, 0);
    meteor->setOnDestroyed([&](){
        this->onMeteorDestroyed();
    });
    this->engine->addObject(meteor);
    this->lastMeteorSpawn = esp_timer_get_time();
}

void FASE1::onMeteorDestroyed() {
    this->score = this->score + 1;
    this->updateScoreDisplay();
}

void FASE1::onMainShipDestroyed() {
    this->mainShipDestroyed = true;
}

void FASE1::opening() {
    CERectangle *rect = new CERectangle();
    rect->setBaseColor({0, 21, 36});
    rect->setHeight(240);
    rect->setWidth(320);
    rect->setPos(0, 0);
    rect->setFilled(true);
    this->engine->addObject(rect);

    CEText *text = new CEText();
    text->setText("20 meteoros\npara passar");
    text->setBaseColor({255, 255, 255});
    text->setSizeMultiplier(3);
    text->setPos(25, 80);
    text->setPriority(2);
    this->engine->addObject(text);

    this->engine->loopAndRender();
    cleytin_delay(3000);

    this->engine->clear(true);
}

void FASE1::gameOver() {
    this->setupBackground(false);

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

void FASE1::updateScoreDisplay() {
    if(this->scoreText == NULL) {
        this->scoreText = new CEText();
        this->scoreText->setBaseColor({182, 255, 250});
        this->scoreText->setPos(10, 10);
        this->scoreText->setColisionEnabled(false);
        this->scoreText->setPriority(10);
        this->scoreText->setSizeMultiplier(2);
        this->engine->addObject(this->scoreText);
    }

    std::string s = std::to_string(this->score);
    this->scoreText->setText(s.c_str());
}

void FASE1::setupBackground(bool withScore) {
    CEColorfulBitmap *bitmap = new CEColorfulBitmap();
    bitmap->setBuffer(sprite_color_bg_01);
    bitmap->setHeight(240);
    bitmap->setWidth(320);
    bitmap->setColisionEnabled(false);
    bitmap->setHasTransparency(false);
    this->engine->addObject(bitmap);

    if(!withScore) return;
    bitmap = new CEColorfulBitmap();
    bitmap->setBuffer(sprite_color_score_bg);
    bitmap->setHeight(34);
    bitmap->setWidth(66);
    bitmap->setAlphaColor(0xFFFF);
    bitmap->setPos(4, 3);
    bitmap->setColisionEnabled(false);
    this->engine->addObject(bitmap);
}

void FASE1::setupMainShip() {
    MainShip *mainShip = new MainShip();
    mainShip->setControls(this->controls);
    mainShip->setAudioInterface(this->audioEngine);
    mainShip->setOnMainShipDestroyed([&](){
        this->onMainShipDestroyed();
    });
    this->engine->addObject(mainShip);
}
