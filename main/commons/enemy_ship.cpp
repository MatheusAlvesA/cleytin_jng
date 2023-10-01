#include "enemy_ship.h"

EnemyShip::EnemyShip(unsigned int id)
{
    this->engine = NULL;
    this->animation = NULL;
    this->lastFire = 0;
    this->fireRate = 500;
    this->onShipDestroyed = NULL;
    this->id = id;
}

EnemyShip::~EnemyShip()
{
    if (this->animation != NULL)
        delete this->animation;
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

void EnemyShip::checkColisions()
{
    if (this->onShipDestroyed == NULL)
    {
        return;
    }

    std::vector<size_t> *r = this->engine->getCollisionsOn(this);
    bool destroyed = false;
    for (size_t i = 0; i < r->size(); i++)
    {
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
    if (destroyed)
    {
        this->engine->markToDelete(this);
        this->onShipDestroyed();
    }
}

void EnemyShip::loop(CleytinEngine *engine)
{
    this->checkColisions();
    if (this->animation != NULL)
        this->animation->loop();
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
        steps->push_back(new CEPoint(280, 50));
        steps->push_back(new CEPoint(10, 50));
        break;
    case 3:
        steps->push_back(new CEPoint(60, 10));
        steps->push_back(new CEPoint(200, 10));
        steps->push_back(new CEPoint(280, 50));
        steps->push_back(new CEPoint(200, 100));
        steps->push_back(new CEPoint(60, 100));
        steps->push_back(new CEPoint(10, 50));
        steps->push_back(new CEPoint(60, 10));
        break;
    default:
        steps->push_back(new CEPoint(50, 0));
        steps->push_back(new CEPoint(200, 0));
        break;
    }
    this->animation->setSteps(steps);
    delete_pointers_vector<CEPoint>(steps);
    this->animation->start();
}

bool EnemyShip::fire()
{
    if (this->engine == NULL)
    {
        return false;
    }
    uint64_t elapsed = esp_timer_get_time() - this->lastFire;
    if (elapsed < this->fireRate * 1000)
    {
        return false;
    }
    this->lastFire = esp_timer_get_time();

    MainLaserBeam *laserBeam = new MainLaserBeam();
    laserBeam->setPos(this->getPosX() + 14, this->getPosY() - 22);
    this->engine->addObject(laserBeam);

    return true;
}
