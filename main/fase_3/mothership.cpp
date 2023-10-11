#include "mothership.h"

Mothership::Mothership(bool startPacifist)
{
    this->engine = NULL;
    this->animation = NULL;
    this->onShipDestroyed = NULL;
    this->leftFireTimer = new CETimer(MOTHERSHIP_FIRE_RATE);
    this->rightFireTimer = new CETimer(MOTHERSHIP_FIRE_RATE + 100);
    this->pacifist = startPacifist;
    this->health = MOTHERSHIP_START_HEALTH;
}

Mothership::~Mothership()
{
    if (this->animation != NULL)
        delete this->animation;
    delete this->leftFireTimer;
    delete this->rightFireTimer;
}

void Mothership::setOnShipDestroyed(std::function<void()> callback)
{
    this->onShipDestroyed = callback;
}

void Mothership::setup(CleytinEngine *engine)
{
    this->setBuffer(sprite_color_mothership);

    this->setHeight(160);
    this->setWidth(167);
    this->setAlphaColor(0x0);
    this->setPos(0, -50);
    this->setPriority(2);
    this->engine = engine;
    this->prepareAnimation();
}

void Mothership::checkColisions()
{
    std::vector<size_t> *r = this->engine->getCollisionsOn(this);
    bool attacked = false;
    for (size_t i = 0; i < r->size(); i++) {
        CEGraphicObject *obj = engine->getObjectAt(r->at(i));
        MainLaserBeam *laser = dynamic_cast<MainLaserBeam *>(obj);
        if (laser == NULL)
        {
            continue;
        }
        // Aconteceu uma colisão com um laser
        attacked = true;
        this->engine->markToDelete(laser);
        break;
    }

    delete r;
    if(attacked) this->takeDamage();
}

void Mothership::takeDamage() {
    if(this->health == 0) return;
    this->health--;
    printf("Mothership health: %d\n", this->health);
    this->animation->setDuration(5000);
    this->pacifist = false;
    if(this->health == 0) {
        this->engine->markToDelete(this);
        if(this->onShipDestroyed != NULL) 
            this->onShipDestroyed();
        this->explosion();
    }
}

void Mothership::explosion()
{
    DefaultExplosion *explosion = new DefaultExplosion();
    explosion->setPos(this->getPosX(), this->getPosY());
    this->engine->addObject(explosion);
}

void Mothership::loop(CleytinEngine *engine)
{
    this->checkColisions();
    this->animation->loop();
    this->fire();
}

void Mothership::prepareAnimation()
{
    if (this->animation != NULL)
        delete this->animation;
    this->animation = new CEMultiLinearMoveAnimation();
    this->animation->setIsLooping(true);
    this->animation->setObject(this);
    this->animation->setDuration(this->pacifist ? 7000 : 5000);
    std::vector<CEPoint *> *steps = new std::vector<CEPoint *>();
    steps->push_back(new CEPoint(0, -50));
    steps->push_back(new CEPoint(60, -30));
    steps->push_back(new CEPoint(90, -10));
    steps->push_back(new CEPoint(120, 0));
    steps->push_back(new CEPoint(140, -10));
    steps->push_back(new CEPoint(180, -40));
    steps->push_back(new CEPoint(0, -50));
    this->animation->setSteps(steps);
    delete_pointers_vector<CEPoint>(steps);
    this->animation->start();
}

void Mothership::fire()
{
    if (this->engine == NULL || this->pacifist)
    {
        return;
    }
    this->fireLeftCannon();
    this->fireRightCannon();
}

void Mothership::fireLeftCannon()
{
    if (!this->leftFireTimer->check())
    {
        return;
    }
    this->leftFireTimer->reset();

    EnemyLaserBeam *laserBeam = new EnemyLaserBeam();
    laserBeam->setPos(this->getPosX() + 47, this->getPosY() + 153);
    this->engine->addObject(laserBeam);
}

void Mothership::fireRightCannon()
{
    if (!this->rightFireTimer->check())
    {
        return;
    }
    this->rightFireTimer->reset();

    EnemyLaserBeam *laserBeam = new EnemyLaserBeam();
    laserBeam->setPos(this->getPosX() + 120, this->getPosY() + 153);
    this->engine->addObject(laserBeam);
}
