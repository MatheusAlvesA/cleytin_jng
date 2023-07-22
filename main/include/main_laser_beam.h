#ifndef MAIN_LASER_BEAM
#define MAIN_LASER_BEAM

#include "cleytin_engine.h"
#include "ce_colorful_bitmap.h"
#include "sprites.h"
#include "cleytin_controls.h"
#include "ce_move_controls.h"
#include "ce_linear_move_animation.h"

class MainLaserBeam : public CEColorfulBitmap {
public:
    void setup(CleytinEngine *engine);
    void loop(CleytinEngine *engine);

private:
    CELinearMoveAnimation *animation;
};

#endif
