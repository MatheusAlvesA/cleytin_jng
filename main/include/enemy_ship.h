#ifndef ENEMY_SHIP
#define ENEMY_SHIP

#include "cleytin_engine.h"
#include "ce_colorful_bitmap.h"
#include "sprites.h"
#include "cleytin_controls.h"
#include "ce_move_controls.h"
#include "main_laser_beam.h"
#include "enemy_laser_beam.h"
#include "default_meteor.h"
#include "cleytin_audio_engine.h"
#include "audios.h"
#include "ce_multi_linear_move_animation.h"
#include "ce_timer.h"
#include "default_explosion.h"
#include <functional>

#define ENEMY_SHIP_FIRE_RATE 2000

class EnemyShip : public CEColorfulBitmap
{
public:
    EnemyShip(unsigned int id);
    ~EnemyShip();
    void setup(CleytinEngine *engine);
    void loop(CleytinEngine *engine);
    void setOnShipDestroyed(std::function<void()> callback);
    void onCompanionDied();

private:
    CleytinEngine *engine;
    bool checkColisions();
    bool fire();
    void prepareAnimation();
    void explosion();
    unsigned int id;
    bool companionDied;
    std::function<void()> onShipDestroyed;
    CEMultiLinearMoveAnimation *animation;
    CETimer *fireTimer;
};

#endif
