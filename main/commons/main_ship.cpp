#include "main_ship.h"

MainShip::MainShip() {
    this->engine = NULL;
    this->controls = NULL;
    this->lastFire = 0;
    this->fireRate = 500;
    this->moveControls = new CEMoveControls();
    this->moveControls->setPixelsPerSecond(100);
}

MainShip::~MainShip() {
    delete this->moveControls;
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

void MainShip::handleControls() {
    if(this->controls == NULL) {
        return;
    }

    if(this->controls->getA()) {
        this->fire();
    }

    this->moveControls->handleControls(this->controls, this);
}

void MainShip::loop(CleytinEngine *engine) {
    this->handleControls();
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

    return true;
}
