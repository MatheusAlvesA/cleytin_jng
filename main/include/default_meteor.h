#ifndef DEFAULT_METEOR_H
#define DEFAULT_METEOR_H

#include "cleytin_engine.h"
#include "ce_colorful_bitmap.h"
#include "sprites.h"
#include "cleytin_controls.h"
#include "ce_move_controls.h"
#include "ce_linear_move_animation.h"

class DefaultMeteor : public CEColorfulBitmap {
public:
    void setup(CleytinEngine *engine);
    void loop(CleytinEngine *engine);

private:
    CELinearMoveAnimation *animation;
};

#endif
