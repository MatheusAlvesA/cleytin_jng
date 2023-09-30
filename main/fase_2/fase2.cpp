#include "fase2.h"

FASE2::FASE2() {
    this->scoreText = NULL;
    this->lastEnemySpawn = 0;
    this->score = 0;
    this->mainShipDestroyed = false;
}

bool FASE2::run(CleytinEngine *engine, CleytinControls *controls, CleytinAudioEngine *audioEngine) {
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
    while(!this->mainShipDestroyed && this->score < FASE_2_SCORE_TO_PASS) {
        uint64_t startLoop = esp_timer_get_time();
        this->spawnEnemy();
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

void FASE2::clean() {
    this->engine->clear(true);
    this->audioEngine->clear();
    this->scoreText = NULL;
    this->mainShipDestroyed = false;
    this->score = 0;
    this->lastEnemySpawn = 0;
}

void FASE2::spawnEnemy() {
    uint64_t elapsed_time_ms = (esp_timer_get_time() - this->lastEnemySpawn) / 1000;

    if(elapsed_time_ms < FASE_2_ENEMY_SPAWN_INTERVAL) {
        return;
    }

    // DefaultMeteor *enemy = new DefaultMeteor();
    // enemy->setPos(rand() % 245, 0);
    // enemy->setOnDestroyed([&](){
    //     this->onEnemyDestroyed();
    // });
    // this->engine->addObject(enemy);
    // this->lastEnemySpawn = esp_timer_get_time();
}

void FASE2::onEnemyDestroyed() {
    this->score = this->score + 1;
    this->updateScoreDisplay();
}

void FASE2::onMainShipDestroyed() {
    this->mainShipDestroyed = true;
}

void FASE2::opening() {
    CERectangle *rect = new CERectangle();
    rect->setBaseColor({0, 0, 0});
    rect->setHeight(240);
    rect->setWidth(320);
    rect->setPos(0, 0);
    rect->setFilled(true);
    this->engine->addObject(rect);

    CEText *text = new CEText();
    text->setText("5 inimigos\npara passar");
    text->setBaseColor({255, 255, 255});
    text->setSizeMultiplier(3);
    text->setPos(25, 80);
    text->setPriority(2);
    this->engine->addObject(text);

    this->engine->render();
    cleytin_delay(3000);

    this->engine->clear(true);
}

void FASE2::gameOver() {
    this->setupBackground(false);

    CEText *text = new CEText();
    text->setText("GAME OVER");
    text->setBaseColor({255, 0, 0});
    text->setSizeMultiplier(3);
    text->setPos(50, 100);
    this->engine->addObject(text);

    while(!this->controls->getStart()) {
        this->engine->render();
    }

    this->engine->clear(true);
}

void FASE2::updateScoreDisplay() {
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
    const char *r = s.c_str();
    this->scoreText->setText(r);
}

void FASE2::setupBackground(bool withScore) {
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

void FASE2::setupMainShip() {
    MainShip *mainShip = new MainShip();
    mainShip->setControls(this->controls);
    mainShip->setAudioInterface(this->audioEngine);
    mainShip->setOnMainShipDestroyed([&](){
        this->onMainShipDestroyed();
    });
    this->engine->addObject(mainShip);
}
