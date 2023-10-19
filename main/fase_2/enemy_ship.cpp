#include "enemy_ship.h"

EnemyShip::EnemyShip(unsigned int id)
{
    this->engine = NULL;
    this->animation = NULL;
    this->onShipDestroyed = NULL;
    this->id = id;
    this->companionDied = false;
    this->fireTimer = new CETimer(ENEMY_SHIP_FIRE_RATE);
}

EnemyShip::~EnemyShip()
{
    if (this->animation != NULL)
        delete this->animation;
    delete this->fireTimer;
}

void EnemyShip::onCompanionDied() {
    this->companionDied = true;
}

void EnemyShip::setOnShipDestroyed(std::function<void()> callback)
{
    this->onShipDestroyed = callback;
}

void EnemyShip::setup(CleytinEngine *engine)
{
    switch (this->id)
    {
    case 0:
        this->setBuffer(sprite_color_ship_01);
        break;
    case 1:
        this->setBuffer(sprite_color_ship_02);
        break;
    case 2:
        this->setBuffer(sprite_color_ship_03);
        break;
    case 3:
        this->setBuffer(sprite_color_ship_04);
        break;
    default:
        this->setBuffer(sprite_color_ship_01);
        break;
    }

    this->setHeight(32);
    this->setWidth(32);
    this->setAlphaColor(0x0);
    this->setPos(144, this->id * 32);
    this->setPriority(9);
    this->engine = engine;
    this->prepareAnimation();
}

bool EnemyShip::checkColisions()
{
    std::vector<size_t> *r = this->engine->getCollisionsOn(this);
    bool destroyed = false;
    for (size_t i = 0; i < r->size(); i++) {
        CEGraphicObject *obj = engine->getObjectAt(r->at(i));
        MainLaserBeam *laser = dynamic_cast<MainLaserBeam *>(obj);
        if (laser == NULL)
        {
            continue;
        }
        // Aconteceu uma colisão com um laser
        destroyed = true;
        break;
    }

    delete r;
    if (destroyed) {
        this->engine->markToDelete(this);
        if(this->onShipDestroyed != NULL) 
            this->onShipDestroyed();
        this->explosion();
    }
    return destroyed;
}

void EnemyShip::explosion()
{
    DefaultExplosion *explosion = new DefaultExplosion();
    explosion->setPos(this->getPosX(), this->getPosY());
    this->engine->addObject(explosion);
}

void EnemyShip::loop(CleytinEngine *engine)
{
    if(this->checkColisions()) {
        return;
    }
    if (this->animation != NULL)
        this->animation->loop();
    this->fire();
}

void EnemyShip::prepareAnimation()
{
    if (this->animation != NULL)
        delete this->animation;
    this->animation = new CEMultiLinearMoveAnimation();
    this->animation->setIsLooping(true);
    this->animation->setObject(this);
    this->animation->setDuration(5000);
    std::vector<CEPoint *> *steps = new std::vector<CEPoint *>();
    switch (this->id)
    {
    case 0:
        steps->push_back(new CEPoint(50, 0));
        steps->push_back(new CEPoint(280, 0));
        steps->push_back(new CEPoint(280, 100));
        steps->push_back(new CEPoint(50, 100));
        steps->push_back(new CEPoint(50, 0));
        break;
    case 1:
        steps->push_back(new CEPoint(140, 0));
        steps->push_back(new CEPoint(280, 100));
        steps->push_back(new CEPoint(50, 100));
        steps->push_back(new CEPoint(140, 0));
        break;
    case 2:
        steps->push_back(new CEPoint(10, 50));
        steps->push_back(new CEPoint(280, 90));
        steps->push_back(new CEPoint(10, 90));
        steps->push_back(new CEPoint(280, 10));
        steps->push_back(new CEPoint(10, 10));
        steps->push_back(new CEPoint(10, 50));
        break;
    case 3:
        steps->push_back(new CEPoint(60, 10));
        steps->push_back(new CEPoint(200, 10));
        steps->push_back(new CEPoint(280, 100));
        steps->push_back(new CEPoint(200, 150));
        steps->push_back(new CEPoint(60, 100));
        steps->push_back(new CEPoint(10, 50));
        steps->push_back(new CEPoint(60, 10));
        break;
    default:
        steps->push_back(new CEPoint(20, 0));
        steps->push_back(new CEPoint(90, 150));
        steps->push_back(new CEPoint(130, 0));
        steps->push_back(new CEPoint(160, 150));
        steps->push_back(new CEPoint(200, 0));
        steps->push_back(new CEPoint(240, 150));
        steps->push_back(new CEPoint(280, 0));
        steps->push_back(new CEPoint(20, 0));
        break;
    }
    this->animation->setSteps(steps);
    delete_pointers_vector<CEPoint>(steps);
    this->animation->start();
}

bool EnemyShip::fire()
{
    if (
        this->engine == NULL ||
        !this->companionDied ||
        !this->fireTimer->check()
    )
    {
        return false;
    }
    this->fireTimer->reset();

    EnemyLaserBeam *laserBeam = new EnemyLaserBeam();
    laserBeam->setPos(this->getPosX() + 14, this->getPosY() + 32);
    this->engine->addObject(laserBeam);

    return true;
}
