#include "jng.h"

JNG::JNG() {
    this->scoreText = NULL;
    this->lastMeteorSpawn = 0;
    this->score = 0;
    this->mainShipDestroyed = false;
    this->audioInterface = NULL;
}

void JNG::run(CleytinEngine *engine) {
    CleytinControls *controls = new CleytinControls();
    controls->init();
    this->audioInterface = new CleytinAudioEngine();
    this->audioInterface->init();
    this->engine = engine;

    while(1) {
        MainShip *mainShip = new MainShip();
        mainShip->setControls(controls);
        mainShip->setAudioInterface(this->audioInterface);
        mainShip->setOnMainShipDestroyed([&](){
            this->onMainShipDestroyed();
        });
        engine->addObject(mainShip);

        uint64_t start = esp_timer_get_time();
        uint64_t sum = 0;
        uint64_t n = 0;
        this->updateScoreDisplay();
        while(!this->mainShipDestroyed) {
            uint64_t startLoop = esp_timer_get_time();
            this->spawnMeteor(engine);
            engine->loop();
            engine->render();
            n++;
            sum = sum + (esp_timer_get_time() - startLoop);
            if((esp_timer_get_time() - start) > 500 * 1000) {
                printf("FPS: %llu | Objects: %u\n", n * 2, engine->getObjectsCount());
                start = esp_timer_get_time();
                sum = 0;
                n = 0;
            }
        }
        this->gameOver(controls);
    }
}

void JNG::spawnMeteor(CleytinEngine *engine) {
    uint64_t elapsed_time_ms = (esp_timer_get_time() - this->lastMeteorSpawn) / 1000;

    if(elapsed_time_ms < METEOR_SPAWN_INTERVAL) {
        return;
    }

    DefaultMeteor *meteor = new DefaultMeteor();
    meteor->setPos(rand() % 280, 0);
    meteor->setOnDestroyed([&](){
        this->onMeteorDestroyed();
    });
    engine->addObject(meteor);
    this->lastMeteorSpawn = esp_timer_get_time();
}

void JNG::onMeteorDestroyed() {
    this->score = this->score + 1;
    this->updateScoreDisplay();
}

void JNG::onMainShipDestroyed() {
    this->mainShipDestroyed = true;
}

void JNG::gameOver(CleytinControls *controls) {
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

void JNG::updateScoreDisplay() {
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
