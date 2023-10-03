#ifndef ENEMY_LASER_BEAM
#define ENEMY_LASER_BEAM

#include "cleytin_engine.h"
#include "ce_colorful_bitmap.h"
#include "sprites.h"
#include "ce_linear_move_animation.h"

class EnemyLaserBeam : public CEColorfulBitmap {
public:
    EnemyLaserBeam();
    ~EnemyLaserBeam();
    void setup(CleytinEngine *engine);
    void loop(CleytinEngine *engine);

private:
    CELinearMoveAnimation *animation;
};

#endif
