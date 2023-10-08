#include "default_explosion.h"

DefaultExplosion::DefaultExplosion() {
    this->animation = new CEColorBitmapSpriteAnimation();
}

DefaultExplosion::~DefaultExplosion() {
    delete this->animation;
}

void DefaultExplosion::setup(CleytinEngine *engine) {
    this->setBuffer(sprite_color_explosion_01);
    this->setHeight(32);
    this->setWidth(32);
    this->setAlphaColor(0xFFFF);
    this->setColisionEnabled(false);

    this->animation->setObject(this);
    this->animation->setDuration(600);
    std::vector<const uint16_t *> *sprites = new std::vector<const uint16_t *>();
    sprites->push_back(sprite_color_explosion_01);
    sprites->push_back(sprite_color_explosion_02);
    sprites->push_back(sprite_color_explosion_03);
    sprites->push_back(sprite_color_explosion_04);
    this->animation->setFramesFrom(sprites);
    delete sprites;
    this->animation->start();
}

void DefaultExplosion::beforeLoop(CleytinEngine *engine) {
    if(this->animation->isFinished()) {
        engine->markToDelete(this);
        return;
    }
}

void DefaultExplosion::loop(CleytinEngine *engine) {
    if(this->animation->isFinished()) {
        return;
    }
    this->animation->loop();
}
