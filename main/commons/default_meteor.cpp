#include "default_meteor.h"

void DefaultMeteor::setup(CleytinEngine *engine) {
    this->setBuffer(sprite_color_meteor_01);
    this->setHeight(40);
    this->setWidth(40);
    this->setAlphaColor(0x0);
    this->animation = new CELinearMoveAnimation();
    this->animation->setObject(this);
    this->animation->setDuration(2000);
    this->animation->setStartPosition(this->getPosX(), this->getPosY());
    this->animation->setEndPosition(this->getPosX(), 240);
    this->animation->start();
}

void DefaultMeteor::loop(CleytinEngine *engine) {
    if(this->animation == NULL) {
        return;
    }
    if(this->animation->isFinished()) {
        delete this->animation;
        this->animation = NULL;
        engine->markToDelete(this);
        return;
    }
    this->animation->loop();
}
