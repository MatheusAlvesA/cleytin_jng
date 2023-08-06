#include "fase1.h"

FASE1::FASE1() {
    this->scoreText = NULL;
    this->lastMeteorSpawn = 0;
    this->score = 0;
    this->mainShipDestroyed = false;
}

bool FASE1::run(CleytinEngine *engine, CleytinControls *controls, CleytinAudioEngine *audioEngine) {
    this->engine = engine;

    CleytinAudio *audio = NULL;
    audioEngine->createAudio(wav_bin_musica_fundo, &audio);
    audio->setLoop(true);
    audio->play();

    while(this->score < SCORE_TO_PASS) {
        this->setupBackground();
        MainShip *mainShip = new MainShip();
        mainShip->setControls(controls);
        mainShip->setAudioInterface(audioEngine);
        mainShip->setOnMainShipDestroyed([&](){
            this->onMainShipDestroyed();
        });
        engine->addObject(mainShip);

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
        if(this->score < SCORE_TO_PASS) {
            this->gameOver(controls);
        }
    }
    engine->clear(true);
    audioEngine->clear();
    return false;
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

void FASE1::gameOver(CleytinControls *controls) {
    this->engine->clear(true);
    this->engine->render();

    CEText *text = new CEText();
    text->setText("GAME OVER");
    text->setBaseColor({255, 0, 0});
    text->setSizeMultiplier(3);
    text->setPos(50, 100);
    this->engine->addObject(text);

    while(!controls->getStart()) {
        this->engine->render();
    }

    this->engine->clear(true);
    this->scoreText = NULL;
    this->engine->render();

    this->mainShipDestroyed = false;
    this->score = 0;
}

void FASE1::updateScoreDisplay() {
    if(this->scoreText == NULL) {
        this->scoreText = new CEText();
        this->scoreText->setBaseColor({255, 0, 255});
        this->scoreText->setPos(10, 10);
        this->scoreText->setColisionEnabled(false);
        this->scoreText->setPriority(100);
        this->scoreText->setSizeMultiplier(2);
        this->engine->addObject(this->scoreText);
    }

    std::string s = std::to_string(this->score);
    this->scoreText->setText(s.c_str());
}

void FASE1::setupBackground() {
    CEColorfulBitmap *bitmap = new CEColorfulBitmap();
    bitmap->setBuffer(sprite_color_bg_01);
    bitmap->setHeight(240);
    bitmap->setWidth(320);
    bitmap->setAlphaColor(0x0);
    bitmap->setColisionEnabled(false);
    bitmap->setHasTransparency(false);
    this->engine->addObject(bitmap);
}
