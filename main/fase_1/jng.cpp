#include "jng.h"

void JNG::run(CleytinEngine *engine) {
    MainShip *mainShip = new MainShip();
    CleytinControls *controls = new CleytinControls();

    controls->init();
    mainShip->setControls(controls);
    engine->addObject(mainShip);

    while(1) { // Essa 'fase' do game nunca termina
        this->spawnMeteor(engine);
        engine->loop();
        engine->render();
    }
}

void JNG::spawnMeteor(CleytinEngine *engine) {
    uint64_t elapsed_time_ms = (esp_timer_get_time() - this->lastMeteorSpawn) / 1000;

    if(elapsed_time_ms < METEOR_SPAWN_INTERVAL) {
        return;
    }

    DefaultMeteor *meteor = new DefaultMeteor();
    meteor->setPos(rand() % 280, 0);
    engine->addObject(meteor);
    this->lastMeteorSpawn = esp_timer_get_time();
}
