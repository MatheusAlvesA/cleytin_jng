#ifndef MOTHERSHIP
#define MOTHERSHIP

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
#include "ce_pixel_shader_animation.h"
#include "ce_timer.h"
#include "default_explosion.h"

#define MOTHERSHIP_FIRE_RATE 2000
#define MOTHERSHIP_START_HEALTH 20

void _mothership_damage_pixel_shader(CEGraphicObject* obj, int x, int y, CEColor *color);

class Mothership : public CEColorfulBitmap
{
public:
    Mothership(bool startPacifist);
    ~Mothership();
    void setup(CleytinEngine *engine);
    void loop(CleytinEngine *engine);
    void setOnShipDestroyed(std::function<void()> callback);

private:
    CleytinEngine *engine;
    void checkColisions();
    void fire();
    void fireLeftCannon();
    void fireRightCannon();
    void prepareAnimation();
    void explosion();
    void takeDamage();
    std::function<void()> onShipDestroyed;
    CEMultiLinearMoveAnimation *animation;
    CEPixelShaderAnimation *damageAnimation;
    CETimer *leftFireTimer;
    CETimer *rightFireTimer;
    bool pacifist;
    uint health;
};

#endif
