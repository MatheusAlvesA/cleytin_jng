#include "main_ship.h"

MainShip::MainShip() {
    this->controls = NULL;
    this->moveControls = new CEMoveControls();
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
}

void MainShip::setControls(CleytinControls *controls) {
    this->controls = controls;
}

void MainShip::handleControls() {
    if(this->controls == NULL) {
        return;
    }

    this->moveControls->handleControls(this->controls, this);
}

void MainShip::loop(CleytinEngine *engine) {
    this->handleControls();
}
