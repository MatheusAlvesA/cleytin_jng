#include "jng.h"

void JNG::run(CleytinEngine *engine) {
    CleytinControls *controls = new CleytinControls();
    controls->init();

    while(1) {
        MainShip *mainShip = new MainShip();
        mainShip->setControls(controls);
        mainShip->setOnMainShipDestroyed([&](){
            this->onMainShipDestroyed();
        });
        engine->addObject(mainShip);

        while(!this->mainShipDestroyed) {
            this->spawnMeteor(engine);
            engine->loop();
            engine->render();
            this->updateScoreDisplay(engine);
        }
        this->gameOver(engine, controls);
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
}

void JNG::onMainShipDestroyed() {
    this->mainShipDestroyed = true;
}

void JNG::gameOver(CleytinEngine *engine, CleytinControls *controls) {
    engine->clear(true);
    engine->render();

    CEText *text = new CEText();
    text->setText("GAME OVER");
    text->setBaseColor({255, 0, 0});
    text->setSizeMultiplier(3);
    text->setPos(50, 100);
    engine->addObject(text);

    while(!controls->getStart()) {
        engine->render();
    }

    engine->clear(true);
    engine->render();

    this->mainShipDestroyed = false;
    this->score = 0;
}

void JNG::updateScoreDisplay(CleytinEngine *engine) {
    if(this->scoreText == NULL) {
        this->scoreText = new CEText();
        this->scoreText->setBaseColor({255, 0, 255});
        this->scoreText->setPos(10, 10);
        this->scoreText->setColisionEnabled(false);
        this->scoreText->setPriority(100);
        this->scoreText->setSizeMultiplier(2);
        engine->addObject(this->scoreText);
    }

    std::string s = std::to_string(this->score);
    this->scoreText->setText(s.c_str());
}
