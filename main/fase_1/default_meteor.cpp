#include "default_meteor.h"

DefaultMeteor::DefaultMeteor() {
    this->animation = NULL;
    this->onDestroyed = NULL;
    this->engine = NULL;
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
    this->engine = engine;

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
        this->despawn();
        return;
    }
    if(this->checkColisions()) {
        return;
    }
    this->animation->loop();
}

bool DefaultMeteor::checkColisions() {
    if(this->onDestroyed == NULL) {
        return false;
    }

    std::vector<size_t> *r = this->engine->getCollisionsOn(this);
    bool destroyed = false;
    for (size_t i = 0; i < r->size(); i++)
    {
        CEGraphicObject *obj = this->engine->getObjectAt(r->at(i));
        MainLaserBeam *laser = dynamic_cast<MainLaserBeam *>(obj);
        if(laser == NULL) {
            continue;
        }
        // Aconteceu uma colisão com um tiro
        destroyed = true;
        this->engine->markToDelete(laser);
        break;
    }

    delete r;
    if(destroyed) {
        this->despawn();
        this->onDestroyed();
        this->explosion();
    }
    return destroyed;
}

void DefaultMeteor::despawn() {
    if(this->animation != NULL) {
        delete this->animation;
        this->animation = NULL;
    }
    this->engine->markToDelete(this);
}

void DefaultMeteor::explosion() {
    DefaultExplosion *explosion = new DefaultExplosion();
    explosion->setSizeMultiplier(2);
    explosion->setPos(this->getPosX(), this->getPosY());
    this->engine->addObject(explosion);
}
