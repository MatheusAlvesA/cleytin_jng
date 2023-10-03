#include "enemy_laser_beam.h"

EnemyLaserBeam::EnemyLaserBeam() {
    this->animation = NULL;
}

EnemyLaserBeam::~EnemyLaserBeam() {
    if(this->animation != NULL) {
        delete this->animation;
        this->animation = NULL;
    }
}

void EnemyLaserBeam::setup(CleytinEngine *engine) {
    this->setBuffer(sprite_color_green_laser_beam);
    this->setHeight(22);
    this->setWidth(4);
    this->setAlphaColor(0x0);
    this->animation = new CELinearMoveAnimation();
    this->animation->setObject(this);
    this->animation->setDuration(600);
    this->animation->setStartPosition(this->getPosX(), this->getPosY());
    this->animation->setEndPosition(this->getPosX(), 310);
    this->animation->start();
}

void EnemyLaserBeam::loop(CleytinEngine *engine) {
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
