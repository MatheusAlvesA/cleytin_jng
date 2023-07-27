#include "main_ship.h"

MainShip::MainShip() {
    this->engine = NULL;
    this->controls = NULL;
    this->lastFire = 0;
    this->fireRate = 500;
    this->moveControls = new CEMoveControls();
    this->moveControls->setPixelsPerSecond(100);
    this->onMainShipDestroyed = NULL;
    this->audioInterface = NULL;
}

MainShip::~MainShip() {
    delete this->moveControls;
}

void MainShip::setOnMainShipDestroyed(std::function<void()> callback) {
    this->onMainShipDestroyed = callback;
}

void MainShip::setup(CleytinEngine *engine) {
    this->setBuffer(sprite_color_main_ship);
    this->setHeight(32);
    this->setWidth(32);
    this->setAlphaColor(0x0);
    this->setPos(144, 208); // Spaw, inferior centro da tela
    this->setPriority(10);
    this->engine = engine;
}

void MainShip::setControls(CleytinControls *controls) {
    this->controls = controls;
}

void MainShip::setAudioInterface(CleytinAudioEngine *interface) {
    this->audioInterface = interface;
}

void MainShip::handleControls() {
    if(this->controls == NULL) {
        return;
    }

    if(this->controls->getA()) {
        this->fire();
    }

    this->moveControls->handleControls(this->controls, this);
}

void MainShip::checkColisions(CleytinEngine *engine) {
    if(this->onMainShipDestroyed == NULL) {
        return;
    }

    std::vector<size_t> *r = engine->getCollisionsOn(this);
    bool destroyed = false;
    for (size_t i = 0; i < r->size(); i++)
    {
        CEGraphicObject *obj = engine->getObjectAt(r->at(i));
        DefaultMeteor *meteor = dynamic_cast<DefaultMeteor *>(obj);
        if(meteor == NULL) {
            continue;
        }
        // Aconteceu uma colisão com um meteoro
        destroyed = true;
        break;
    }

    delete r;
    if(destroyed) {
        this->onMainShipDestroyed();
    }
}

void MainShip::loop(CleytinEngine *engine) {
    this->handleControls();
    this->checkColisions(engine);
}

bool MainShip::fire() {
    if(this->engine == NULL) {
        return false;
    }
    uint64_t elapsed = esp_timer_get_time() - this->lastFire;
    if(elapsed < this->fireRate * 1000) {
        return false;
    }
    this->lastFire = esp_timer_get_time();

    MainLaserBeam *laserBeam = new MainLaserBeam();
    laserBeam->setPos(this->getPosX() + 14, this->getPosY() - 22);
    this->engine->addObject(laserBeam);

    if(this->audioInterface != NULL) {
        this->audioInterface->playOnce(wav_bin_laser_default);
    }

    return true;
}
