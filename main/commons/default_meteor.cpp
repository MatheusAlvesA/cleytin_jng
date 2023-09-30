#include "default_meteor.h"

DefaultMeteor::DefaultMeteor() {
    this->animation = NULL;
    this->onDestroyed = NULL;
}

DefaultMeteor::~DefaultMeteor() {
    if(this->animation != NULL) {
        delete this->animation;
        this->animation = NULL;
    }
}

void DefaultMeteor::setOnDestroyed(std::function<void()> callback) {
    this->onDestroyed = callback;
}

void DefaultMeteor::setup(CleytinEngine *engine) {
    this->setBuffer(sprite_color_meteor_01);
    this->setHeight(63);
    this->setWidth(75);
    this->setAlphaColor(0xF8);
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
        this->despawn(engine);
        return;
    }
    if(this->checkColisions(engine)) {
        return;
    }
    this->animation->loop();
}

bool DefaultMeteor::checkColisions(CleytinEngine *engine) {
    if(this->onDestroyed == NULL) {
        return false;
    }

    std::vector<size_t> *r = engine->getCollisionsOn(this);
    bool destroyed = false;
    for (size_t i = 0; i < r->size(); i++)
    {
        CEGraphicObject *obj = engine->getObjectAt(r->at(i));
        MainLaserBeam *laser = dynamic_cast<MainLaserBeam *>(obj);
        if(laser == NULL) {
            continue;
        }
        // Aconteceu uma colisão com um tiro
        destroyed = true;
        engine->markToDelete(laser);
        break;
    }

    delete r;
    if(destroyed) {
        this->despawn(engine);
        this->onDestroyed();
    }
    return destroyed;
}

void DefaultMeteor::despawn(CleytinEngine *engine) {
    if(this->animation != NULL) {
        delete this->animation;
        this->animation = NULL;
    }
    engine->markToDelete(this);
}
